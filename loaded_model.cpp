#include "loaded_model.h"


loaded_model::loaded_model(const shader_struct& shader_s, const std::string& path, const glm::vec3& position, const glm::vec3& direction, const float& size) : model(shader_s) {
	obj_path = path;
	this->position = position;
	this->direction = direction;
	this->size = size;
}

void loaded_model::create() {
	load_mesh(obj_path);
}

void loaded_model::draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix) {
	glUseProgram(shader_s.program);

	set_transformation_uniforms(projection_matrix, view_matrix, model_matrix);
	set_material_uniforms(ambient, diffuse, specular, shininess, texture);

	// draw geometry
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_of_triangles * 3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void loaded_model::load_mesh(const std::string & file_name) {
	glUseProgram(shader_s.program);

	std::vector<unsigned int> indices;

	Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);
	// Load asset from the file - you can play with various processing steps
	const aiScene * scn = importer.ReadFile(file_name.c_str(), 0
		| aiProcess_Triangulate             // Triangulate polygons (if any).
		| aiProcess_PreTransformVertices    // Transforms scene hierarchy into one root with geometry-leafs only. For more see Doc.
		| aiProcess_GenSmoothNormals        // Calculate normals per vertex.
		| aiProcess_JoinIdenticalVertices);

	// abort if the loader fails
	if (scn == NULL) {
		std::cerr << "assimp error: " << importer.GetErrorString() << std::endl;
		return;
	}

	// some formats store whole scene (multiple meshes and materials, lights, cameras, ...) in one file, we cannot handle that in our simplified example
	if (scn->mNumMeshes != 1) {
		std::cerr << "this simplified loader can only process files with only one mesh" << std::endl;
		return;
	}

	const aiMesh * mesh = scn->mMeshes[0];

	aiFace *face;
	for (unsigned int f = 0; f<mesh->mNumFaces; f++) {
      face = &mesh->mFaces[f];
      indices.push_back(face->mIndices[0]);
      indices.push_back(face->mIndices[1]);
      indices.push_back(face->mIndices[2]);
	}

	num_of_triangles = mesh->mNumFaces;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * mesh->mNumVertices * sizeof(float), 0, GL_STATIC_DRAW); // alocate memory for vertices, normals, texture coords

	glBufferSubData(GL_ARRAY_BUFFER, 0, mesh->mNumVertices * sizeof(float) * 3, mesh->mVertices); // store vertices 
	glBufferSubData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(float) * 3, mesh->mNumVertices * sizeof(float) * 3, mesh->mNormals); // store normals
	
	// just texture 0 for now
	float *textureCoords = new float[2 * mesh->mNumVertices];  // 2 floats per vertex
	float *currentTextureCoord = textureCoords;
	// copy texture coordinates
	aiVector3D vect;
	if (mesh->HasTextureCoords(0)) {
		// we use 2D textures with 2 coordinates and ignore the third coordinate
		for (unsigned int idx = 0; idx < mesh->mNumVertices; idx++) {
			vect = (mesh->mTextureCoords[0])[idx];
			*currentTextureCoord++ = vect.x;
			*currentTextureCoord++ = vect.y;
		}
	}
	// finally store all texture coordinates
	glBufferSubData(GL_ARRAY_BUFFER, 6 * sizeof(float)*mesh->mNumVertices, 2 * sizeof(float)*mesh->mNumVertices, textureCoords);
	// copy the material info
	const aiMaterial *mat = scn->mMaterials[mesh->mMaterialIndex];
	aiColor4D color;
	aiString name;
	aiReturn retValue = AI_SUCCESS;

	// Get returns: aiReturn_SUCCESS 0 | aiReturn_FAILURE -1 | aiReturn_OUTOFMEMORY -3
	mat->Get(AI_MATKEY_NAME, name); // may be "" after the input mesh processing. Must be aiString type!
	if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color)) != AI_SUCCESS)
		color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);

	diffuse = glm::vec3(color.r, color.g, color.b);

	if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color)) != AI_SUCCESS)
		color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
	ambient = glm::vec3(color.r, color.g, color.b);

	if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color)) != AI_SUCCESS)
		color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
	specular = glm::vec3(color.r, color.g, color.b);

	ai_real shininess, strength;
	unsigned int max;	// changed: to unsigned

	max = 1;
	if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS, &shininess, &max)) != AI_SUCCESS)
		shininess = 1.0f;
	max = 1;
	if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS_STRENGTH, &strength, &max)) != AI_SUCCESS)
		strength = 1.0f;
	this->shininess = shininess * strength;

	texture = 0;
	// load texture image
	if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		// get texture name 
		aiString path; // filename

		aiReturn texFound = mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		std::string textureName = path.data;

		size_t found = file_name.find_last_of("/\\");
		// insert correct texture file path 
		if (found != std::string::npos) { // not found
		  //subMesh_p->textureName.insert(0, "/");
			textureName.insert(0, file_name.substr(0, found + 1));
		}

		std::cout << "Loading texture file: " << textureName << std::endl;
		texture = pgr::createTexture(textureName);
	}

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(shader_s.position_loc);
	glVertexAttribPointer(shader_s.position_loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(shader_s.normal_loc);
	glVertexAttribPointer(shader_s.normal_loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * mesh->mNumVertices));

	glEnableVertexAttribArray(shader_s.texture_coord_loc);
	glVertexAttribPointer(shader_s.texture_coord_loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)(6 * sizeof(float) * mesh->mNumVertices));

	CHECK_GL_ERROR();
	glBindVertexArray(0);
	glUseProgram(0);
}

void loaded_model::set_material_uniforms(const glm::vec3 & ambient, const glm::vec3 & diffuse, const glm::vec3 & specular, float shininess, GLuint texture) {
	glUniform3fv(shader_s.diffuse_loc, 1, glm::value_ptr(diffuse));  // 2nd parameter must be 1 - it declares number of vectors in the vector array
	glUniform3fv(shader_s.ambient_loc, 1, glm::value_ptr(ambient));
	glUniform3fv(shader_s.specular_loc, 1, glm::value_ptr(specular));
	glUniform1f(shader_s.shininess_loc, shininess);
	glUniform1i(shader_s.rotate_texture_loc, 0);

	if (texture != 0) {
		glUniform1i(shader_s.use_texture_loc, 1);
		glUniform1i(shader_s.tex_sampler_loc, 0);  // texturing unit 0 -> samplerID   [for the GPU linker]
		glActiveTexture(GL_TEXTURE0 + 0);                  // texturing unit 0 -> to be bound [for OpenGL BindTexture]
		glBindTexture(GL_TEXTURE_2D, texture);
	} else {
		glUniform1i(shader_s.use_texture_loc, 0);  // do not sample the texture
	}
}
