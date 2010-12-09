#pragma once

class Exception : public std::runtime_error
{
	public:
		Exception(std::string description, std::string where): mDescription(description), mWhere(where), std::runtime_error(description) {};
		~Exception(void) {};

		const char* getDescription() { return mDescription.c_str(); }

	private:
		Exception();

		std::string mDescription;
		std::string mWhere;
};
