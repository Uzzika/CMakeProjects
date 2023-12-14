// Copyright 2022 Marina Usova

#include <gtest.h>
#include "../lib_example/example.h"

#define EPSILON 0.000001

TEST(test_ExampleClass, can_create_with_default_constructor) {
    // Arrange & Act & Assert
    ASSERT_NO_THROW(ExampleClass<int> obj);
}

TEST(test_ExampleClass, can_create_with_constructor_by_size) {
    // Arrange & Act & Assert
    ASSERT_NO_THROW(ExampleClass<int> obj(10));
}

TEST(test_ExampleClass, throw_when_create_with_constructor_by_negative_size) {
    // Arrange & Act & Assert
    ASSERT_ANY_THROW(ExampleClass<int> obj(-10));
}

TEST(test_ExampleClass, throw_when_create_with_constructor_by_too_large_size) {
    // Arrange & Act & Assert
    ASSERT_ANY_THROW(ExampleClass<int> obj(INT_MAX + 1));
}

TEST(test_ExampleClass, can_get_size) {
    // Arrange
    ExampleClass<int> obj(10);

    // Act & Assert
    ASSERT_NO_THROW(obj.getSize());
    EXPECT_EQ(obj.getSize(), 10);
}

TEST(test_ExampleClass, can_set_and_get_value) {
    // Arrange
    ExampleClass<int> obj(10);

    obj.setValue(3, 5);

    // Act & Assert
    ASSERT_NO_THROW(obj.getValue(5));
    EXPECT_EQ(obj.getValue(3), 5);
}

TEST(test_ExampleClass, throw_when_position_in_set_is_out_of_range_1) {
    // Arrange
    ExampleClass<int> obj(10);
    // Act & Assert
    ASSERT_ANY_THROW(obj.setValue(-5, 5));
}

TEST(test_ExampleClass, throw_when_position_in_set_is_out_of_range_2) {
    // Arrange
    ExampleClass<int> obj(10);
    // Act & Assert
    ASSERT_ANY_THROW(obj.setValue(11, 5));
}

TEST(test_ExampleClass, throw_when_position_in_get_is_out_of_range_1) {
    // Arrange
    ExampleClass<int> obj(10);
    // Act & Assert
    ASSERT_ANY_THROW(obj.getValue(-1));
}

TEST(test_ExampleClass, throw_when_position_in_get_is_out_of_range_2) {
    // Arrange
    ExampleClass<int> obj(10);
    // Act & Assert
    ASSERT_ANY_THROW(obj.getValue(15));
}

TEST(test_ExampleClass, can_set_rand_values) {
    // Arrange
    srand(time(NULL));
    ExampleClass<int> obj(10);
    // Act & Assert
    ASSERT_NO_THROW(obj.setRandValues(-100, 100));
    int success = 1;
    for (int i = 0; i < obj.getSize(); i++) {
        EXPECT_LE(obj.getValue(i), 100);
        EXPECT_GE(obj.getValue(i), -100);
    }
}

TEST(test_ExampleClass, can_convert_to_string) {
    // Arrange
    ExampleClass<int> obj(10);

    // Act
    for (int i = 0; i < obj.getSize(); i++) {
        obj.setValue(i, (i + 1) * 10);
    }
    std::string expectedResult = "10 20 30 40 50 60 70 80 90 100 ";
    // Assert
    EXPECT_EQ(expectedResult, obj.toString());
}
