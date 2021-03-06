/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "RankThreeTensor.h"
#include "RankTwoTensor.h"
#include "RankFourTensor.h"

// MOOSE includes
#include "MooseEnum.h"
#include "MooseException.h"
#include "MooseUtils.h"
#include "MatrixTools.h"
#include "MaterialProperty.h"
#include "PermutationTensor.h"

// libMesh includes
#include "libmesh/utility.h"

// C++ includes
#include <iomanip>
#include <ostream>

template <>
void
mooseSetToZero<RankThreeTensor>(RankThreeTensor & v)
{
  v.zero();
}

template <>
void
dataStore(std::ostream & stream, RankThreeTensor & rtht, void * context)
{
  dataStore(stream, rtht._vals, context);
}

template <>
void
dataLoad(std::istream & stream, RankThreeTensor & rtht, void * context)
{
  dataLoad(stream, rtht._vals, context);
}

MooseEnum RankThreeTensor::fillMethodEnum() // TODO: Need new fillMethodEnum() -- for now we will
                                            // just use general (at most 27 components)
{
  return MooseEnum("general");
}

RankThreeTensor::RankThreeTensor()
{
  mooseAssert(N == 3, "RankThreeTensor is currently only tested for 3 dimensions.");

  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        _vals[i][j][k] = 0.0;
}

RankThreeTensor::RankThreeTensor(const InitMethod init)
{
  switch (init)
  {
    case initNone:
      break;

    default:
      mooseError("Unknown RankThreeTensor initialization pattern.");
  }
}

RankThreeTensor::RankThreeTensor(const std::vector<Real> & input, FillMethod fill_method)
{
  fillFromInputVector(input, fill_method);
}

Real &
RankThreeTensor::operator()(unsigned int i, unsigned int j, unsigned int k)
{
  return _vals[i][j][k];
}

Real
RankThreeTensor::operator()(unsigned int i, unsigned int j, unsigned int k) const
{
  return _vals[i][j][k];
}

void
RankThreeTensor::zero()
{
  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        _vals[i][j][k] = 0.0;
}

RankThreeTensor &
RankThreeTensor::operator=(const RankThreeTensor & a)
{
  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        _vals[i][j][k] = a(i, j, k);

  return *this;
}

RankThreeTensor RankThreeTensor::operator*(const Real b) const
{
  RankThreeTensor result;
  const RankThreeTensor & a = *this;

  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        result(i, j, k) = a(i, j, k) * b;

  return result;
}

RankThreeTensor &
RankThreeTensor::operator*=(const Real a)
{
  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        _vals[i][j][k] *= a;

  return *this;
}

RankThreeTensor
RankThreeTensor::operator/(const Real b) const
{
  RankThreeTensor result;
  const RankThreeTensor & a = *this;

  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        result(i, j, k) = a(i, j, k) / b;

  return result;
}

RankThreeTensor &
RankThreeTensor::operator/=(const Real a)
{
  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        _vals[i][j][k] /= a;

  return *this;
}

RankThreeTensor &
RankThreeTensor::operator+=(const RankThreeTensor & a)
{
  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        _vals[i][j][k] += a(i, j, k);

  return *this;
}

RankThreeTensor
RankThreeTensor::operator+(const RankThreeTensor & b) const
{
  RankThreeTensor result;
  const RankThreeTensor & a = *this;

  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        result(i, j, k) = a(i, j, k) + b(i, j, k);

  return result;
}

RankThreeTensor &
RankThreeTensor::operator-=(const RankThreeTensor & a)
{
  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        _vals[i][j][k] -= a(i, j, k);

  return *this;
}

RankThreeTensor
RankThreeTensor::operator-(const RankThreeTensor & b) const
{
  RankThreeTensor result;
  const RankThreeTensor & a = *this;

  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        result(i, j, k) = a(i, j, k) - b(i, j, k);

  return result;
}

RankThreeTensor
RankThreeTensor::operator-() const
{
  RankThreeTensor result;
  const RankThreeTensor & a = *this;

  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        result(i, j, k) = -a(i, j, k);

  return result;
}

Real
RankThreeTensor::L2norm() const
{
  Real l2 = 0;
  const RankThreeTensor & a = *this;

  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        l2 += Utility::pow<2>(a(i, j, k));

  return std::sqrt(l2);
}

void
RankThreeTensor::fillFromInputVector(const std::vector<Real> & input, FillMethod fill_method)
{
  zero();

  switch (fill_method)
  {
    case general:
      fillGeneralFromInputVector(input);
      break;
    default:
      mooseError("fillFromInputVector called with unknown fill_method of ", fill_method);
  }
}

void
RankThreeTensor::rotate(const RealTensorValue & R)
{
  RankThreeTensor old = *this;

  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
      {
        Real sum = 0.0;
        for (unsigned int m = 0; m < N; ++m)
          for (unsigned int n = 0; n < N; ++n)
            for (unsigned int o = 0; o < N; ++o)
              sum += R(i, m) * R(j, n) * R(k, o) * old(m, n, o);

        _vals[i][j][k] = sum;
      }
}

void
RankThreeTensor::rotate(const RankTwoTensor & R)
{
  RankThreeTensor old = *this;

  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
      {
        Real sum = 0.0;
        for (unsigned int m = 0; m < N; ++m)
          for (unsigned int n = 0; n < N; ++n)
            for (unsigned int o = 0; o < N; ++o)
              sum += R(i, m) * R(j, n) * R(k, o) * old(m, n, o);

        _vals[i][j][k] = sum;
      }
}

void
RankThreeTensor::fillGeneralFromInputVector(const std::vector<Real> & input)
{
  if (input.size() != 27)
    mooseError("To use fillGeneralFromInputVector, your input must have size 27. Yours has size ",
               input.size());

  int ind;
  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
      {
        ind = i * N * N + j * N + k;
        _vals[i][j][k] = input[ind];
      }
}
