
#ifndef _ELEMENT_QUEUE_H
#define _ELEMENT_QUEUE_H

struct Element
{
  explicit Element(const char *p_msg);
  ~Element();
  const char *msg;
  virtual void outputValue(ofstream& sdlog) const = 0;
};

template <class TYPE>
struct LogElement : public Element
{
  explicit LogElement(const char *p_msg, TYPE const val);
  void outputValue(ofstream& sdlog) const;
  void outputValue(String& str) const;
  TYPE const value;
};

struct ElementQueue
{
  ElementQueue();
  ~ElementQueue();
  ElementQueue(const ElementQueue& another);
  void push(Element* elem);
  bool peek() const;
  Element* pop();

private:
  static const int maximum = 11;
  int numOf;
  Element* elems[maximum];

};

#endif
