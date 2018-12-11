#include "aiv_unit_test.h"
#include "blackcolor.h"

TEST(increment_gradient)
{
	ASSERT_THAT(black + increment == 0x030303ff)
}

int main(int argc, char **argv)
{
	RUN_TEST(increment_gradient);
	PRINT_TEST_RESULTS();
	return 0;
}
