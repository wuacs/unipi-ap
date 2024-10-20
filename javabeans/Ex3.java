/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.ap24;
import java.beans.IntrospectionException;
import java.lang.reflect.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.beans.*;

/**
 *
 * @author dario
 */
public class Ex3 {
    
    public static List<Field> getAllFields(List<Field> fields, Class<?> type) {
        fields.addAll(Arrays.asList(type.getDeclaredFields()));

        if (type.getSuperclass() != null) {
            getAllFields(fields, type.getSuperclass());
        }

        return fields;
    }
    
    public static void main(String args[]) throws 
                                            java.lang.IndexOutOfBoundsException,
                                            ClassNotFoundException,
                                            IntrospectionException
    {
        final String bean_name = args[0];
        final Class bean_class = Class.forName(bean_name);
        final List<Field> fields = getAllFields(new LinkedList(), bean_class);
        for (final Field field : fields) {
            String field_name = field.getName();
            try {
                bean_class.getMethod("set"+field_name.substring(0, 1).toUpperCase()+field_name.substring(1), field.getType());
                System.out.println("Property " + field.getName() + " is read-write");
            } catch (NoSuchMethodException ex) {
                System.out.println("Property " + field.getName() + " is read-only");
            }
        }
        
        EventSetDescriptor[] events = (Introspector.getBeanInfo(bean_class)).getEventSetDescriptors();
        for (final EventSetDescriptor esd : events) {
            System.out.println("Bean allows to subscribe listeners of type: " + esd.getListenerType().getName());
        }
        
    }
}
