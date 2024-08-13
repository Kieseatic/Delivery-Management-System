#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "TruckInfo_r.h"
#include "configure_r.h"
#include "customerShipment_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitWhiteTest
{
	TEST_CLASS(truckTestWhite)
	{
		const struct Map baseMap = populateMap();
	public:
		TEST_METHOD(TruckTwo)
		{
			configure();
			struct Point destination = { -10,-10 };
			struct ShipmentInfo package = { -500, -15, destination };
			int result = getTruck(package);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(TruckThree)
		{
			configure();
			struct Point destination = { 12,12 };
			struct ShipmentInfo package = { 901, 30, destination };
			int result = getTruck(package);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(TruckFour)
		{
			configure();
			struct Point destination = { 24,24 };
			struct ShipmentInfo package = { 500, 15, destination };
			int result = getTruck(package);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(TruckFive)
		{
			configure();
			struct Point destination = { 50,50 };
			struct ShipmentInfo package = { 500, 15, destination };
			int result = getTruck(package);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(TruckSix)
		{
			configure();
			struct Point destination = { 10,10 };
			struct ShipmentInfo package = { 500, 15, destination };
			int result = getTruck(package);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TruckSeven)
		{
			configure();
			struct Point destination = { 10,10 };
			struct ShipmentInfo package = { 900, 30, destination };
			int result = getTruck(package);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(SpaceOne) {
			int weight = 900;
			double vol = 9;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(1.1, result);
		}
		TEST_METHOD(SpaceTwo) {
			int weight = 200;
			double vol = 10;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(0.22, result);
		};
		TEST_METHOD(SpaceThree) {
			int weight = 300;
			double vol = 0;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(0.0, result);
		};
		TEST_METHOD(SpaceFour) {
			int weight = 0;
			double vol = 10;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(0.0, result);
		};
		TEST_METHOD(SpaceFive) {
			int weight = -250;
			double vol = -5;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(0.554, result);
		};
		TEST_METHOD(ValidateOne_WhiteBox) {
			struct Point destination1 = { 10, 10 };
			int result1 = validateShipment(5, 500, destination1);
			Assert::AreEqual(-1, result1);
		}
		TEST_METHOD(ValidateTwo_WhiteBox) {
			struct Point destination2 = { 10, 10 };
			int result2 = validateShipment(CAP_VOL_ONE, 2000, destination2);
			Assert::AreEqual(-2, result2);
		}
		TEST_METHOD(ValidateThree_WhiteBox) {
			struct Point destination3 = { 0, 0 };
			int result3 = validateShipment(CAP_VOL_ONE, 500, destination3);
			Assert::AreEqual(-3, result3);
		}
		TEST_METHOD(ValidateFour_WhiteBox) {
			struct Point destination4 = { 10, 10 };
			int result4 = validateShipment(CAP_VOL_TWO, 500, destination4);
			Assert::AreEqual(1, result4);
		}
		TEST_METHOD(ValidateFive_WhiteBox) {
			struct Point destination5 = { 10, 10 };
			int result5 = validateShipment(CAP_VOL_THREE, 500, destination5);
			Assert::AreEqual(1, result5);
		}
	};
}