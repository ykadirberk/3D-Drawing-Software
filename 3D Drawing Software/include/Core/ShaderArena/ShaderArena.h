#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <optional>

#include "../DLLBuild.h"
#include "../Shader/Shader.h"

namespace dra {
	class _API ShaderArena {
	public:
		[[nodiscard]] static ShaderArena& Instance();

		void LoadShader(std::string& name, std::string& file_path);
		void BindShader(std::string& shader_name);

		[[nodiscard]] std::optional<std::shared_ptr<Shader>> GetShader(std::string& shader_name) noexcept;
		private:
			ShaderArena();
			~ShaderArena();
			ShaderArena(ShaderArena& shader_arena) = delete;
			ShaderArena(ShaderArena&& shader_arena) = delete;

			std::unordered_map<std::string, std::shared_ptr<Shader>> m_ShaderList;
	};
}