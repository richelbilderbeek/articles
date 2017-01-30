/*
///The problem

#include <cassert>
#include <boost/shared_ptr.hpp>

struct Test
{
  Test(const int x = 0) : m_x(x) {}
  int m_x;
};

struct Source
{
  Source() : m_test(new Test(1)) {}

  ///Note the added constness
  boost::shared_ptr<const Test> Get() const { return m_test; }

  void SetTest(const boost::shared_ptr<Test>& test) { m_test = test; }

  private:
  boost::shared_ptr<Test> m_test;
};

struct Observer
{
  boost::shared_ptr<const Test> Get() const { return m_test; }

  void SetTest(const boost::shared_ptr<const Test>& test) { m_test = test; }

  private:
  boost::shared_ptr<const Test> m_test;
};


int main()
{
  Source source;
  Observer observer;
  observer.SetTest(source.Get());
  assert(source.Get()->m_x == 1);
  assert(observer.Get()->m_x == 1);

  ///Put another Test in the Source, makes Observer observing an older Test
  source.SetTest(boost::shared_ptr<Test>(new Test(2)));
  assert(source.Get()->m_x == 2);
  assert(observer.Get()->m_x == 2); //Observer still has old version
}

*/

/*

///The solution: boost::weak_ptr

#include <cassert>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

struct Test
{
  Test(const int x = 0) : m_x(x) {}
  int m_x;
};


struct Source
{
  Source() : m_test(new Test(1)) {}

  ///Note the added constness
  boost::shared_ptr<const Test> Get() const { return m_test; }

  void SetTest(const boost::shared_ptr<Test>& test) { m_test = test; }

  private:
  boost::shared_ptr<Test> m_test;
};

struct Observer
{
  boost::weak_ptr<const Test> Get() const { return m_test; }

  ///Change: use of boost::weak_ptr
  void SetTest(const boost::weak_ptr<const Test>& test) { m_test = test; }

  private:
  ///Change: use of boost::weak_ptr
  boost::weak_ptr<const Test> m_test;
};


int main()
{
  Source source;
  Observer observer;
  observer.SetTest(source.Get());
  assert(source.Get()->m_x == 1);
  assert(observer.Get().lock()->m_x == 1);

  ///Put another Test in the Source, makes Observer observing an older Test
  source.SetTest(boost::shared_ptr<Test>(new Test(2)));
  assert(source.Get()->m_x == 2);
  assert(observer.Get().lock()->m_x == 2); //Good: run-time error: 'Assertion 'px != 0' failed'.
}
*/


///The solution: std::weak_ptr
#include <memory>
#include <cassert>

struct Test
{
  Test(const int x = 0) : m_x(x) {}
  int m_x;
};


struct Source
{
  Source() : m_test(new Test(1)) {}

  ///Note the added constness
  std::shared_ptr<const Test> Get() const { return m_test; }

  void SetTest(const std::shared_ptr<Test>& test) { m_test = test; }

  private:
  std::shared_ptr<Test> m_test;
};

struct Observer
{
  std::weak_ptr<const Test> Get() const { return m_test; }

  ///Change: use of boost::weak_ptr
  void SetTest(const std::weak_ptr<const Test>& test) { m_test = test; }

  private:
  ///Change: use of boost::weak_ptr
  std::weak_ptr<const Test> m_test;
};

int main()
{
  Source source;
  Observer observer;
  observer.SetTest(source.Get());
  assert(source.Get()->m_x == 1);
  assert(observer.Get().lock()->m_x == 1);

  ///Put another Test in the Source, makes Observer observing an older Test
  source.SetTest(std::shared_ptr<Test>(new Test(2)));
  assert(source.Get()->m_x == 2);
  assert(observer.Get().lock()->m_x == 2); //Mediocre: segmentation fault, but no reason is given
}
