
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

// ...

/* ************************************************************************** */

void lasdtest();

void mytest();

// Aux to print vector by MapFunction
template <typename Data>
void PrintItems(Data& x, void* p);

// Auxiliarities functions for FoldFunction
template <typename Data>
void Adding(const Data& x, const void* par, void* acc);

template <typename Data>
void Multiplying(const Data& x, const void* par, void* acc);

template <typename Data>
void Concat(const Data& s, const void* par, void* sc);

// Auxiliarities functions for MapFunctions
template <typename Data>
inline void Doubled(Data& x, void* p);

template <typename Data>
inline void Squared(Data& x, void* p);

template <typename Data>
void UpperCased(Data& s, void* p);

#endif
