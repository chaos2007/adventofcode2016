package com.donpollitz.day06

import org.scalatest.FunSuite
import org.scalatest.BeforeAndAfter

class RepetitionEncodingTests extends FunSuite with BeforeAndAfter {

  var encoding: RepetitionEncoding = _

  before {
    encoding = new RepetitionEncoding 
  }

  test("new encoding has no message") {
    assert(encoding.getCurrentMessage == "")
  }

  // mark that you want a test here in the future
  test ("test input text from example - part 1") (pending)
  test ("test input text from example - part 2") (pending)
  test ("test input text from problem - part 1") (pending)
  test ("test input text from problem - part 2") (pending)

}
