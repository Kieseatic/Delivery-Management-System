#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "TruckInfo_r.h"
#include "configure_r.h"
#include "customerShipment_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(truckTestBLACK)
	{
		const struct Map baseMap = populateMap();
	public:
		TEST_METHOD(TruckTwo)
		{
			configure();
			struct Point destination = { 10,10 };
			struct ShipmentInfo package = { 500, 15, destination };
			int result = getTruck(package);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(TruckThree)
		{
			configure();
			struct Point destination = { 24,24 };
			struct ShipmentInfo package = { 950, 10, destination };
			int result = getTruck(package);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(TruckFour)
		{
			configure();
			struct Point destination = { 12,12 };
			struct ShipmentInfo package = { 800, 35, destination };
			int result = getTruck(package);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(TruckFive)
		{
			configure();
			struct Point destination = { 0,0 };
			struct ShipmentInfo package = { 950, 35, destination };
			int result = getTruck(package);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(TruckSix)
		{
			configure();
			struct Point destination = { 50,50 };
			struct ShipmentInfo package = { 0, 0, destination };
			int result = getTruck(package);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(SpaceOne) {
			int weight = 450;
			double vol = 15;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(1.0, result);
		};
		TEST_METHOD(SpaceTwo) {
			int weight = 900;
			double vol = 30;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(1.0, result);
		};
		TEST_METHOD(SpaceThree) {
			int weight = 0;
			double vol = 15;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(0.0, result);
		};
		TEST_METHOD(SpaceFour) {
			int weight = 450;
			double vol = 0;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(0.0, result);
		};
		TEST_METHOD(SpaceFive) {
			int weight = -450;
			double vol = 15;
			double result = spaceConsumption(weight, vol);
			Assert::AreEqual(0.0, result);
		};
		TEST_METHOD(ValidateOne) {
			struct Point destination1 = { 10, 10 };
			int result1 = validateShipment(CAP_VOL_ONE, 500, destination1);
			Assert::AreEqual(1, result1);
		}
		TEST_METHOD(ValidateTwo) {
			struct Point destination2 = { 10, 10 };
			int result2 = validateShipment(CAP_VOL_ONE, 0, destination2);
			Assert::AreEqual(-2, result2);
		}
		TEST_METHOD(ValidateThree) {
			struct Point destination3 = { 10, 10 };
			int result3 = validateShipment(0, 500, destination3);
			Assert::AreEqual(-1, result3);
		}
		TEST_METHOD(ValidateFour) {
			struct Point destination4 = { -1, -1 };
			int result4 = validateShipment(CAP_VOL_ONE, 500, destination4);
			Assert::AreEqual(-3, result4);
		}
		TEST_METHOD(ValidateFive) {
			struct Point destination5 = { 'x', 0 };
			int result5 = validateShipment(0, 0, destination5);
			Assert::AreEqual(0, result5);
		}
	};
}