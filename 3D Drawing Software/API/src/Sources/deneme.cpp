#include "../Core/deneme.h"

#include <iostream>

namespace deneme {
	
		Deneme::Deneme() {
			std::cout << "Deneme objesi olusturuldu." << std::endl;
		}

		Deneme::~Deneme() {
			std::cout << "Deneme objesi yok edildi." << std::endl;
		}

		void Deneme::Yazdir() {
			std::cout << "Deneme yazisi yazdirildi." << std::endl;
		}
}