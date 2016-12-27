package com.donpollitz.day06

import scala.collection.mutable.ArrayBuffer
import scala.collection.mutable.Map
import scala.io.Source

class RepetitionEncoding {
  private val entropy = new ArrayBuffer[collection.mutable.Map[Char,Int]]()
  def getCurrentMessage : String = {
    var ret_val = "";
    for( i <- entropy ) {
      ret_val += i.maxBy(_._2)._1
    }
    return ret_val 
  }
  def getCurrentMessage_reverse : String = {
    var ret_val = "";
    for( i <- entropy ) {
      ret_val += i.minBy(_._2)._1
    }
    return ret_val 
  }
  def addEntropy(s: String) {
    for( i <- s.indices) {
    
      if( entropy.size <= i ) {
        entropy += Map()
      }
      var x = entropy(i)
      if( !x.contains(s(i)) ) {
        x(s(i)) = 1
      } else {
        x(s(i)) = x(s(i)) + 1
      }
      entropy(i) = x
    }
  }
  def read_from_file(s: String) {
    for( line <- Source.fromFile(s).getLines ) 
      addEntropy(line)
  }
}
