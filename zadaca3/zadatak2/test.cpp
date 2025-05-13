#include "Number.hpp"
#include <iostream>

int main() {
	// Kreiranje brojeva za testiranje
	Number num1(123);
	Number num2(-456);

	// Testiranje operatora +, -, +=, -= sa drugim brojevima
	Number sum = num1 + num2;
	Number diff = num1 - num2;

	std::cout << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;
	std::cout << num1 << " - " << num2 << " = " << num1 - num2 << std::endl;

	sum += diff;
	diff -= sum;

	std::cout << sum << " + " << diff << " = " << sum + diff << std::endl;
	std::cout << diff << " - " << sum << " = " << diff - sum << std::endl;


	// Testiranje operatora +, -, +=, -= sa konstantnim vrednostima
	sum = sum + 100;
	std::cout << sum << " + " << 100 << " = " << sum + 100 << std::endl;

	diff = diff - 50;
	std::cout << diff << " - " << 50 << " = " << diff - 50 << std::endl;

	sum += 200;
	std::cout << sum << " + " << 200 << " = " << sum + 200 << std::endl;

	diff -= 300;
	std::cout << diff << " - " << 300 << " = " << diff - 300 << std::endl;


	// Testiranje operatora ==, !=, >, <, >=, <= sa drugim brojevima
	bool equal = (num1 == num2);

	std::cout << std::boolalpha << num1 << " == " << num2 << ": " << (num1 == num2) << std::endl;

	bool not_equal = (num1 != num2);
	std::cout << std::boolalpha << num1 << " != " << num2 << ": " << (num1 != num2) << std::endl;

	bool greater = (num1 > num2);
	std::cout << std::boolalpha << num1 << " > " << num2 << ": " << (num1 > num2) << std::endl;

	bool less = (num1 < num2);
	std::cout << std::boolalpha << num1 << " < " << num2 << ": " << (num1 < num2) << std::endl;

	bool greater_equal = (num1 >= num2);
	std::cout << std::boolalpha << num1 << " >= " << num2 << ": " << (num1 >= num2) << std::endl;

	bool less_equal = (num1 <= num2);
	std::cout << std::boolalpha << num1 << " <= " << num2 << ": " << (num1 <= num2) << std::endl;

	// Testiranje operatora ==, !=, >, <, >=, <= sa konstantnim vrednostima
	equal = (num1 == 123);
	std::cout << std::boolalpha << num1 << " == " << 123 << ": " << (num1 == 123) << std::endl;

	not_equal = (num2 != -456);
	std::cout << std::boolalpha << num2 << " != " << -456 << ": " << (num2 != -456) << std::endl;

	greater = (num1 > -100);
	std::cout << std::boolalpha << num1 << " > " << -100 << ": " << (num1 > -100) << std::endl;

	less = (num2 < 500);
	std::cout << std::boolalpha << num1 << " < " << 500 << ": " << (num2 <  500) << std::endl;

	greater_equal = (num1 >= 50);
	std::cout << std::boolalpha << num1 << " >= " << 50 << ": " << (num1 >= 50) << std::endl;

	less_equal = (num2 <= -500);
	std::cout << std::boolalpha << num2 << " <= " << -500 << ": " << (num2 <= -500) << std::endl;


	// Testiranje stepenovanja
	Number power = num1 ^ short(2);

	std::cout << num1 << " ^ " << 2 << " = " << (num1 ^ short(2)) << std::endl;

	// Testiranje operatora bool()
	if (num1)
		std::cout << "num1 je validan broj." << std::endl;
	else
		std::cout << "num1 nije validan broj." << std::endl;

	// Testiranje prefiksnog i postfiksnog inkrementa i dekrementa
	// Number post_inc = num1++;
	std::cout << "num1 = " << num1 << "\tnum1++ " << " = " << num1++ << std::endl;

	// Number pre_inc = ++num2;
	std::cout << "num2 = " << num2 << "\t++num2 " << " = " << ++num2 << std::endl;

	// Number post_dec = num1--;
	std::cout << "num1 = " << num1 << "\tnum1-- " << " = " << num1-- << std::endl;

	// Number pre_dec = --num2;
	std::cout << "num2 = " << num2 << "\t--num1 " << " = " << --num2 << std::endl;

	// Ispis rezultata
	// std::cout << "Suma: " << sum << std::endl;
	// std::cout << "Razlika: " << diff << std::endl;
	// std::cout << "Jednaki: " << equal << std::endl;
	// std::cout << "Nisu jednaki: " << not_equal << std::endl;
	// std::cout << "Veći: " << greater << std::endl;
	// std::cout << "Manji: " << less << std::endl;
	// std::cout << "Veći ili jednak: " << greater_equal << std::endl;
	// std::cout << "Manji ili jednak: " << less_equal << std::endl;
	// std::cout << "Stepenovanje: " << power << std::endl;
	// std::cout << "Postfiksni inkrement: " << post_inc << std::endl;
	// std::cout << "Prefiksni inkrement: " << pre_inc << std::endl;
	// std::cout << "Postfiksni dekrement: " << post_dec << std::endl;
	// std::cout << "Prefiksni dekrement: " << pre_dec << std::endl;

	return 0;
}

