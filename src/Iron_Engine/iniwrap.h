#pragma once

#include "Core.hpp"
#include <string>
#include <Iron_Engine/Core.hpp>
#include <Iron_Engine/vendor/ini_rw/src/ini_rw.h>
/*
* Wrapper for ini_rw
* ini_rw is a mod of ini made by nightmareci
* ini made by rxi
*/

namespace iniwrap {
	
	template <typename T>
	void checkInt(T x)
	{
		if (!x)
		{
			ERROR("Error accesing variable: ");
			ERROR(variable.data());
			ERROR("Error accessing variable in section:");
			ERROR(section.data());

			exit(-1);
		}
	}

	static void loadINI(ini_t*& ini, std::string_view path)
	{
		ini = ini_load(path.data());
		if (!ini)
		{
			ERROR("While loading INI file: ");
			ERROR(path.data());

			exit(-1);
		}
	}

	static const char* readValueS(ini_t*& ini, std::string_view section, std::string_view variable)
	{
		const char* pv = ini_get(ini, section.data(), variable.data());
		checkInt(pv);

		return pv;
	}

	static int writeValueS(ini_t*& ini, std::string_view file, std::string_view section, std::string_view variable, std::string_view value)
	{
		unsigned int i = ini_set(ini, section.data(), variable.data(), value.data());
		checkInt(i);
		checkInt(ini_save(ini, file.data()));
		return i;
	}
	template <typename T>
	static int writeValue(ini_t*& ini, std::string_view file, std::string_view section, std::string_view variable, T value)
	{
		return writeValueS(ini, file, section, variable, std::to_string(value));
	}

	template <typename T>
	static T readValue(ini_t*& ini, std::string_view section, std::string_view variable)
	{
		std::string str = readValueS(ini, section, variable);
		if (str == "true" || str == "false")
			return str == "true";
		
		return static_cast<T>(std::stof(str));
	}
};