#pragma once

namespace Emile {
  template<class T>
  class ICalculatable {
  public:
    virtual T add(T) = 0;
    virtual T sub(T) = 0;
    virtual T mul(T) = 0;
    virtual T div(T) = 0;
    virtual T mod(T) = 0;
    virtual T eq(T) = 0;
    virtual T ne(T) = 0;
    virtual T ge(T) = 0;
    virtual T gt(T) = 0;
    virtual T le(T) = 0;
    virtual T lt(T) = 0;
    // virtual T nt();
  };
}
