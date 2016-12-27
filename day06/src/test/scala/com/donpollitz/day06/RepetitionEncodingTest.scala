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

  test("single entropy is default password.") {
    encoding.addEntropy("eedadn")
    assert(encoding.getCurrentMessage == "eedadn")
  }

  test("multiple entropy is chooses max.") {
    encoding.addEntropy("eedadn")
    encoding.addEntropy("zzzzzz")
    encoding.addEntropy("zzzzzz")
    assert(encoding.getCurrentMessage == "zzzzzz")
  }

  test ("test input text from example - part 1") {
    encoding.read_from_file("example_1.txt")
    assert(encoding.getCurrentMessage == "easter")
  }

  test ("test input text from example - part 2") {
    encoding.read_from_file("part_1.txt")
    assert(encoding.getCurrentMessage == "qrqlznrl")
  }

  test ("test input text from problem - part 1") {
    encoding.read_from_file("example_1.txt")
    assert(encoding.getCurrentMessage_reverse == "advent")
  }

  test ("test input text from problem - part 2") {
    encoding.read_from_file("part_1.txt")
    assert(encoding.getCurrentMessage_reverse == "kgzdfaon")
  }

}
