#ifndef UTIL_H
#define UTIL_H

/**
 * @brief mark an variable unused
 * 
 * good for making the compiler shut up about unused variables
 * 
 * @param expr the varibale which will be marked unused
 */
#define UNUSED(expr) do { (void)(expr); } while (0);

#endif
