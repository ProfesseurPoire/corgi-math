#include <corgi/math/Vec4.h>
#include <corgi/math/MathUtils.h>
#include <corgi/test/test.h>

using namespace corgi::math;
using namespace corgi;
using namespace std;
using namespace corgi::test;

TEST(ut_vec4, Constructors)
{
	corgi::vec4 u;
	assert_that(u.x, equals(0.0f));
	assert_that(u.y, equals(0.0f));
	assert_that(u.z, equals(0.0f));
	assert_that(u.w, equals(0.0f));

	corgi::vec4 v(1.0f, 2.0f, 3.0f, 2.0f);
	assert_that(v.x, equals(1.0f));
	assert_that(v.y, equals(2.0f));
	assert_that(v.z, equals(3.0f));
	assert_that(v.w, equals(2.0f));
}

// TEST(ut_vec4, check_comparison)
// {
// 	assert_that(zero, equals(zero));
// 	assert_that(zero, non_equals(one));
// }

// TEST(ut_vec4, check_cross_product)
// {
// 	assert_that(right.cross(up), equals(forward));
// }

// TEST(ut_vec4, check_lerp)
// {
// 	assert_that(corgi::Vec4::lerp(zero, corgi::Vec4(10.0f, 10.0f, 10.0f, 10.0f), 0.5f),
// 		equals(corgi::Vec4(5.0f, 5.0f, 5.0, 5.0f)));
// }

// TEST(ut_vec4, check_length)
// {
// 	assert_that(corgi::Vec4(4.0f, 4.0f, 2.0f, 0.0f).length(), equals(6.0f));
// }

// TEST(ut_vec4, check_sqrt_length)
// {
// 	assert_that(corgi::Vec4(2.0f, 3.0f, 5.0f, 0.0f).sqrt_length(), equals(38.0f));
// }

TEST(ut_vec4, check_substraction)
{
	assert_that(vec4::one() - vec4::one(), equals(vec4::zero()));
}

// TEST(ut_vec4, check_unary_substraction)
// {
// 	assert_that(-one, equals(corgi::Vec4(-1.0f, -1.0f, -1.0f, -1.0f)));
// }

TEST(ut_vec4, check_addition)
{
	assert_that(vec4::one() + vec4::one(), equals(corgi::vec4(2.0f, 2.0f, 2.0f, 2.0f)));
}

// TEST(ut_vec4, check_multiplication)
// {
// 	assert_that(corgi::Vec4(2.0f, 3.0f, 4.0f, 1.0f)*corgi::Vec4(2.0f, 3.0f, 4.0f, 1.0f),
// 		equals(corgi::Vec4(4.0f, 9.0f, 16.0f, 1.0f)));

// 	assert_that(corgi::Vec4(2.0f, 3.0f, 4.0f, 1.0f)*2.0f,
// 		equals(corgi::Vec4(4.0f, 6.0f, 8.0f, 2.0f)));
// }

// TEST(ut_vec4, Division)
// {
// 	assert_that(corgi::Vec4(10.0f, 8.0f, 6.0f, 0.0f) / 2.0f,
// 		equals(corgi::Vec4(5.0f, 4.0f, 3.0f, 0.0f)));
// }

// TEST(ut_vec4, AssignmentMutliplication)
// {
// 	assert_that(corgi::Vec4(2.0f, 3.0f, 4.0f, 5.0f) *= corgi::Vec4(2.0f, 3.0f, 4.0f, 5.0f),
// 		equals(corgi::Vec4(4.0f, 9.0f, 16.0f, 25.0f)));

// 	assert_that(corgi::Vec4(2.0f, 3.0f, 4.0f, 1.0f) *= 2.0f,
// 		equals(corgi::Vec4(4.0f, 6.0f, 8.0f, 2.0f)));
// }

// TEST(ut_vec4, check_assignment_addition)
// {
// 	assert_that(corgi::Vec4(2.0f, 3.0f, 5.0f, 1.0f) += corgi::Vec4(1.0f, 3.0f, 2.0f, 1.0f),
// 		equals(corgi::Vec4(3.0f, 6.0f, 7.0f, 2.0f)));
// }

// TEST(ut_vec4, check_assignment_substraction)
// {
// 	assert_that(corgi::Vec4(2.0f, 3.0f, 5.0f, 1.0f) -= corgi::Vec4(2.0f, 3.0f, 5.0f, 1.0f),
// 		equals(corgi::Vec4(0.0f, 0.0f, 0.0f, 0.0f)));
// }

// TEST(ut_vec4, check_assignment_division)
// {
// 	assert_that(corgi::Vec4(2.0f, 4.0f, 6.0f, 2.0f) /= 2.0f,
// 		equals(corgi::Vec4(1.0f, 2.0f, 3.0f, 1.0f)));
// }

