/**
 * @file util.c
 * @brief global util file
 * @author diekmann
 *
 * 
 *
 * @date 24.02.2011 – first implementation
 * @date 24.02.2011 – change x
 *
 * @todo  sth
 *
 * @test yeah ...
 *
 * @bug may be 
 *
 * @version 0.1
 */



/**
 * @brief greatest common divisor
 *
 * calculate the greates common divisor
 *
 * @param a int
 * @param b int
 * @return int
 */
int gcd(int a, int b)
{
	if(b == 0) return a;
	if(b > a) return gcd(b, a);
	return gcd(a-b, b);
}
