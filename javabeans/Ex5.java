/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.ap24;

import java.lang.annotation.*;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

@Retention(RetentionPolicy.RUNTIME)
@interface Test {
    String result ();
}

/**
 *
 * @author dario
 */
public class Ex5 {
    
    @Test(result="4")
    public static String test1() {
        return "3";
    }
    
    public static void main(String[] args) throws ClassNotFoundException,
                                                IllegalAccessException,
                                                InvocationTargetException {
        final Class c = Class.forName(args[0]);
        final Method[] m = c.getDeclaredMethods();
        for (Method method : m) {
            Test t = (Test)method.getAnnotation(Test.class);
            if (t != null) {
                Object res = method.invoke(null); // Works only with static methods
                if (((String)res).equals(t.result())) {
                   System.out.println("Test name: " + method.getName() + " Ok!"); 
                } else {
                    System.out.println("Test name: " + method.getName() + " Ko!"); 
                }
                
            }
        }
    }
}
