#include "Utils.h"

namespace Utils
{
	template<typename T>
	inline T GetInfo(json* jsontoexploit, const char* infoname)
	{
		//V�rifie si le json contient l'information demandee
		if (!jsontoexploit->contains(infoname)) {
			std::cerr << "Erreur : " << infoname << " n'existe pas dans ce json" << std::endl;
			return T();
		}

		T val = jsontoexploit->at(infoname);
		return val;
	}

	template<typename T>
	T GetInfoFromArray(json* jsontoexploit, const char* arrayName, const char* infoname)
	{
		//V�rifie si le json contient un �l�ment portant le nom du tableau
		if (!jsontoexploit->contains(arrayName)) {
			std::cerr << "Erreur : " << arrayName << " n'existe pas dans ce json" << std::endl;
			return T();
		}

		//V�rifie si cet �l�ment est un tableau
		if (!jsontoexploit->at(arrayName).is_object()) {
			std::cerr << "Erreur : "<< arrayName <<" est au mauvais format"<< std::endl;
			return T();
		}

		json jumpData = jsontoexploit->at(arrayName);

		//V�rifie si le tableau contient l'information demandee
		if (!jumpData.contains(infoname)) {
			std::cerr << "Erreur : " << infoname << " n'existe pas dans " << arrayName << std::endl;
			return T();
		}

		T val = jumpData[infoname];

		return val;


	}
}
