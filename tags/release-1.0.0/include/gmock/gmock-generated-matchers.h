// This file was GENERATED by a script.  DO NOT EDIT BY HAND!!!

// Copyright 2008, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Google Mock - a framework for writing C++ mock classes.
//
// This file implements some commonly used variadic matchers.

#ifndef GMOCK_INCLUDE_GMOCK_GMOCK_GENERATED_MATCHERS_H_
#define GMOCK_INCLUDE_GMOCK_GMOCK_GENERATED_MATCHERS_H_

#include <sstream>
#include <string>
#include <vector>
#include <gmock/gmock-matchers.h>

namespace testing {
namespace internal {

// Implements ElementsAre() and ElementsAreArray().
template <typename Container>
class ElementsAreMatcherImpl : public MatcherInterface<Container> {
 public:
  typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
  typedef typename RawContainer::value_type Element;

  // Constructs the matcher from a sequence of element values or
  // element matchers.
  template <typename InputIter>
  ElementsAreMatcherImpl(InputIter first, size_t count) {
    matchers_.reserve(count);
    InputIter it = first;
    for (size_t i = 0; i != count; ++i, ++it) {
      matchers_.push_back(MatcherCast<const Element&>(*it));
    }
  }

  // Returns true iff 'container' matches.
  virtual bool Matches(Container container) const {
    if (container.size() != count())
      return false;

    typename RawContainer::const_iterator container_iter = container.begin();
    for (size_t i = 0; i != count();  ++container_iter, ++i) {
      if (!matchers_[i].Matches(*container_iter))
        return false;
    }

    return true;
  }

  // Describes what this matcher does.
  virtual void DescribeTo(::std::ostream* os) const {
    if (count() == 0) {
      *os << "is empty";
    } else if (count() == 1) {
      *os << "has 1 element that ";
      matchers_[0].DescribeTo(os);
    } else {
      *os << "has " << Elements(count()) << " where\n";
      for (size_t i = 0; i != count(); ++i) {
        *os << "element " << i << " ";
        matchers_[i].DescribeTo(os);
        if (i + 1 < count()) {
          *os << ",\n";
        }
      }
    }
  }

  // Describes what the negation of this matcher does.
  virtual void DescribeNegationTo(::std::ostream* os) const {
    if (count() == 0) {
      *os << "is not empty";
      return;
    }

    *os << "does not have " << Elements(count()) << ", or\n";
    for (size_t i = 0; i != count(); ++i) {
      *os << "element " << i << " ";
      matchers_[i].DescribeNegationTo(os);
      if (i + 1 < count()) {
        *os << ", or\n";
      }
    }
  }

  // Explains why 'container' matches, or doesn't match, this matcher.
  virtual void ExplainMatchResultTo(Container container,
                                    ::std::ostream* os) const {
    if (Matches(container)) {
      // We need to explain why *each* element matches (the obvious
      // ones can be skipped).

      bool reason_printed = false;
      typename RawContainer::const_iterator container_iter = container.begin();
      for (size_t i = 0; i != count(); ++container_iter, ++i) {
        ::std::stringstream ss;
        matchers_[i].ExplainMatchResultTo(*container_iter, &ss);

        const string s = ss.str();
        if (!s.empty()) {
          if (reason_printed) {
            *os << ",\n";
          }
          *os << "element " << i << " " << s;
          reason_printed = true;
        }
      }
    } else {
      // We need to explain why the container doesn't match.
      const size_t actual_count = container.size();
      if (actual_count != count()) {
        // The element count doesn't match.  If the container is
        // empty, there's no need to explain anything as Google Mock
        // already prints the empty container.  Otherwise we just need
        // to show how many elements there actually are.
        if (actual_count != 0) {
          *os << "has " << Elements(actual_count);
        }
        return;
      }

      // The container has the right size but at least one element
      // doesn't match expectation.  We need to find this element and
      // explain why it doesn't match.
      typename RawContainer::const_iterator container_iter = container.begin();
      for (size_t i = 0; i != count(); ++container_iter, ++i) {
        if (matchers_[i].Matches(*container_iter)) {
          continue;
        }

        *os << "element " << i << " doesn't match";

        ::std::stringstream ss;
        matchers_[i].ExplainMatchResultTo(*container_iter, &ss);
        const string s = ss.str();
        if (!s.empty()) {
          *os << " (" << s << ")";
        }
        return;
      }
    }
  }

 private:
  static Message Elements(size_t count) {
    return Message() << count << (count == 1 ? " element" : " elements");
  }

  size_t count() const { return matchers_.size(); }
  std::vector<Matcher<const Element&> > matchers_;
};

// Implements ElementsAre() of 0-10 arguments.

class ElementsAreMatcher0 {
 public:
  ElementsAreMatcher0() {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&>* const matchers = NULL;
    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 0));
  }
};

template <typename T1>
class ElementsAreMatcher1 {
 public:
  explicit ElementsAreMatcher1(const T1& e1) : e1_(e1) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 1));
  }

 private:
  const T1& e1_;
};

template <typename T1, typename T2>
class ElementsAreMatcher2 {
 public:
  ElementsAreMatcher2(const T1& e1, const T2& e2) : e1_(e1), e2_(e2) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
      MatcherCast<const Element&>(e2_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 2));
  }

 private:
  const T1& e1_;
  const T2& e2_;
};

template <typename T1, typename T2, typename T3>
class ElementsAreMatcher3 {
 public:
  ElementsAreMatcher3(const T1& e1, const T2& e2, const T3& e3) : e1_(e1),
      e2_(e2), e3_(e3) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
      MatcherCast<const Element&>(e2_),
      MatcherCast<const Element&>(e3_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 3));
  }

 private:
  const T1& e1_;
  const T2& e2_;
  const T3& e3_;
};

template <typename T1, typename T2, typename T3, typename T4>
class ElementsAreMatcher4 {
 public:
  ElementsAreMatcher4(const T1& e1, const T2& e2, const T3& e3,
      const T4& e4) : e1_(e1), e2_(e2), e3_(e3), e4_(e4) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
      MatcherCast<const Element&>(e2_),
      MatcherCast<const Element&>(e3_),
      MatcherCast<const Element&>(e4_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 4));
  }

 private:
  const T1& e1_;
  const T2& e2_;
  const T3& e3_;
  const T4& e4_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5>
class ElementsAreMatcher5 {
 public:
  ElementsAreMatcher5(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
      const T5& e5) : e1_(e1), e2_(e2), e3_(e3), e4_(e4), e5_(e5) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
      MatcherCast<const Element&>(e2_),
      MatcherCast<const Element&>(e3_),
      MatcherCast<const Element&>(e4_),
      MatcherCast<const Element&>(e5_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 5));
  }

 private:
  const T1& e1_;
  const T2& e2_;
  const T3& e3_;
  const T4& e4_;
  const T5& e5_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6>
class ElementsAreMatcher6 {
 public:
  ElementsAreMatcher6(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
      const T5& e5, const T6& e6) : e1_(e1), e2_(e2), e3_(e3), e4_(e4),
      e5_(e5), e6_(e6) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
      MatcherCast<const Element&>(e2_),
      MatcherCast<const Element&>(e3_),
      MatcherCast<const Element&>(e4_),
      MatcherCast<const Element&>(e5_),
      MatcherCast<const Element&>(e6_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 6));
  }

 private:
  const T1& e1_;
  const T2& e2_;
  const T3& e3_;
  const T4& e4_;
  const T5& e5_;
  const T6& e6_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7>
class ElementsAreMatcher7 {
 public:
  ElementsAreMatcher7(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
      const T5& e5, const T6& e6, const T7& e7) : e1_(e1), e2_(e2), e3_(e3),
      e4_(e4), e5_(e5), e6_(e6), e7_(e7) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
      MatcherCast<const Element&>(e2_),
      MatcherCast<const Element&>(e3_),
      MatcherCast<const Element&>(e4_),
      MatcherCast<const Element&>(e5_),
      MatcherCast<const Element&>(e6_),
      MatcherCast<const Element&>(e7_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 7));
  }

 private:
  const T1& e1_;
  const T2& e2_;
  const T3& e3_;
  const T4& e4_;
  const T5& e5_;
  const T6& e6_;
  const T7& e7_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8>
class ElementsAreMatcher8 {
 public:
  ElementsAreMatcher8(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
      const T5& e5, const T6& e6, const T7& e7, const T8& e8) : e1_(e1),
      e2_(e2), e3_(e3), e4_(e4), e5_(e5), e6_(e6), e7_(e7), e8_(e8) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
      MatcherCast<const Element&>(e2_),
      MatcherCast<const Element&>(e3_),
      MatcherCast<const Element&>(e4_),
      MatcherCast<const Element&>(e5_),
      MatcherCast<const Element&>(e6_),
      MatcherCast<const Element&>(e7_),
      MatcherCast<const Element&>(e8_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 8));
  }

 private:
  const T1& e1_;
  const T2& e2_;
  const T3& e3_;
  const T4& e4_;
  const T5& e5_;
  const T6& e6_;
  const T7& e7_;
  const T8& e8_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9>
class ElementsAreMatcher9 {
 public:
  ElementsAreMatcher9(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
      const T5& e5, const T6& e6, const T7& e7, const T8& e8,
      const T9& e9) : e1_(e1), e2_(e2), e3_(e3), e4_(e4), e5_(e5), e6_(e6),
      e7_(e7), e8_(e8), e9_(e9) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
      MatcherCast<const Element&>(e2_),
      MatcherCast<const Element&>(e3_),
      MatcherCast<const Element&>(e4_),
      MatcherCast<const Element&>(e5_),
      MatcherCast<const Element&>(e6_),
      MatcherCast<const Element&>(e7_),
      MatcherCast<const Element&>(e8_),
      MatcherCast<const Element&>(e9_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 9));
  }

 private:
  const T1& e1_;
  const T2& e2_;
  const T3& e3_;
  const T4& e4_;
  const T5& e5_;
  const T6& e6_;
  const T7& e7_;
  const T8& e8_;
  const T9& e9_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10>
class ElementsAreMatcher10 {
 public:
  ElementsAreMatcher10(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
      const T5& e5, const T6& e6, const T7& e7, const T8& e8, const T9& e9,
      const T10& e10) : e1_(e1), e2_(e2), e3_(e3), e4_(e4), e5_(e5), e6_(e6),
      e7_(e7), e8_(e8), e9_(e9), e10_(e10) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    const Matcher<const Element&> matchers[] = {
      MatcherCast<const Element&>(e1_),
      MatcherCast<const Element&>(e2_),
      MatcherCast<const Element&>(e3_),
      MatcherCast<const Element&>(e4_),
      MatcherCast<const Element&>(e5_),
      MatcherCast<const Element&>(e6_),
      MatcherCast<const Element&>(e7_),
      MatcherCast<const Element&>(e8_),
      MatcherCast<const Element&>(e9_),
      MatcherCast<const Element&>(e10_),
    };

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(matchers, 10));
  }

 private:
  const T1& e1_;
  const T2& e2_;
  const T3& e3_;
  const T4& e4_;
  const T5& e5_;
  const T6& e6_;
  const T7& e7_;
  const T8& e8_;
  const T9& e9_;
  const T10& e10_;
};

// Implements ElementsAreArray().
template <typename T>
class ElementsAreArrayMatcher {
 public:
  ElementsAreArrayMatcher(const T* first, size_t count) :
      first_(first), count_(count) {}

  template <typename Container>
  operator Matcher<Container>() const {
    typedef GMOCK_REMOVE_CONST(GMOCK_REMOVE_REFERENCE(Container)) RawContainer;
    typedef typename RawContainer::value_type Element;

    return MakeMatcher(new ElementsAreMatcherImpl<Container>(first_, count_));
  }

 private:
  const T* const first_;
  const size_t count_;
};

}  // namespace internal

// ElementsAre(e0, e1, ..., e_n) matches an STL-style container with
// (n + 1) elements, where the i-th element in the container must
// match the i-th argument in the list.  Each argument of
// ElementsAre() can be either a value or a matcher.  We support up to
// 10 arguments.
//
// NOTE: Since ElementsAre() cares about the order of the elements, it
// must not be used with containers whose elements's order is
// undefined (e.g. hash_map).

inline internal::ElementsAreMatcher0 ElementsAre() {
  return internal::ElementsAreMatcher0();
}

template <typename T1>
inline internal::ElementsAreMatcher1<T1> ElementsAre(const T1& e1) {
  return internal::ElementsAreMatcher1<T1>(e1);
}

template <typename T1, typename T2>
inline internal::ElementsAreMatcher2<T1, T2> ElementsAre(const T1& e1,
    const T2& e2) {
  return internal::ElementsAreMatcher2<T1, T2>(e1, e2);
}

template <typename T1, typename T2, typename T3>
inline internal::ElementsAreMatcher3<T1, T2, T3> ElementsAre(const T1& e1,
    const T2& e2, const T3& e3) {
  return internal::ElementsAreMatcher3<T1, T2, T3>(e1, e2, e3);
}

template <typename T1, typename T2, typename T3, typename T4>
inline internal::ElementsAreMatcher4<T1, T2, T3, T4> ElementsAre(const T1& e1,
    const T2& e2, const T3& e3, const T4& e4) {
  return internal::ElementsAreMatcher4<T1, T2, T3, T4>(e1, e2, e3, e4);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline internal::ElementsAreMatcher5<T1, T2, T3, T4,
    T5> ElementsAre(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
    const T5& e5) {
  return internal::ElementsAreMatcher5<T1, T2, T3, T4, T5>(e1, e2, e3, e4, e5);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6>
inline internal::ElementsAreMatcher6<T1, T2, T3, T4, T5,
    T6> ElementsAre(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
    const T5& e5, const T6& e6) {
  return internal::ElementsAreMatcher6<T1, T2, T3, T4, T5, T6>(e1, e2, e3, e4,
      e5, e6);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7>
inline internal::ElementsAreMatcher7<T1, T2, T3, T4, T5, T6,
    T7> ElementsAre(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
    const T5& e5, const T6& e6, const T7& e7) {
  return internal::ElementsAreMatcher7<T1, T2, T3, T4, T5, T6, T7>(e1, e2, e3,
      e4, e5, e6, e7);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8>
inline internal::ElementsAreMatcher8<T1, T2, T3, T4, T5, T6, T7,
    T8> ElementsAre(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
    const T5& e5, const T6& e6, const T7& e7, const T8& e8) {
  return internal::ElementsAreMatcher8<T1, T2, T3, T4, T5, T6, T7, T8>(e1, e2,
      e3, e4, e5, e6, e7, e8);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9>
inline internal::ElementsAreMatcher9<T1, T2, T3, T4, T5, T6, T7, T8,
    T9> ElementsAre(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
    const T5& e5, const T6& e6, const T7& e7, const T8& e8, const T9& e9) {
  return internal::ElementsAreMatcher9<T1, T2, T3, T4, T5, T6, T7, T8, T9>(e1,
      e2, e3, e4, e5, e6, e7, e8, e9);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10>
inline internal::ElementsAreMatcher10<T1, T2, T3, T4, T5, T6, T7, T8, T9,
    T10> ElementsAre(const T1& e1, const T2& e2, const T3& e3, const T4& e4,
    const T5& e5, const T6& e6, const T7& e7, const T8& e8, const T9& e9,
    const T10& e10) {
  return internal::ElementsAreMatcher10<T1, T2, T3, T4, T5, T6, T7, T8, T9,
      T10>(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10);
}

// ElementsAreArray(array) and ElementAreArray(array, count) are like
// ElementsAre(), except that they take an array of values or
// matchers.  The former form infers the size of 'array', which must
// be a static C-style array.  In the latter form, 'array' can either
// be a static array or a pointer to a dynamically created array.

template <typename T>
inline internal::ElementsAreArrayMatcher<T> ElementsAreArray(
    const T* first, size_t count) {
  return internal::ElementsAreArrayMatcher<T>(first, count);
}

template <typename T, size_t N>
inline internal::ElementsAreArrayMatcher<T>
ElementsAreArray(const T (&array)[N]) {
  return internal::ElementsAreArrayMatcher<T>(array, N);
}

}  // namespace testing

#endif  // GMOCK_INCLUDE_GMOCK_GMOCK_GENERATED_MATCHERS_H_