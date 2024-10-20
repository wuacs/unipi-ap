package com.mycompany.ap24;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Beans/Bean.java to edit this template
 */

import java.io.Serializable;
/**
 *
 * @author dario
 */
public class TempLabel extends javax.swing.JLabel implements Serializable {
    
    public TempLabel() {
        super();
    }
    
    /**
     * Override setText to convert Celsius to Fahrenheit
     * and display the Fahrenheit value.
     * @param celsiusValue String representing the Celsius value
     */
    @Override
    public void setText(String celsiusValue) {
        try {
            // Convert Celsius to Fahrenheit
            double celsius = Double.parseDouble(celsiusValue);
            double fahrenheit = (celsius * 9 / 5) + 32;
            // Set Fahrenheit value as the label text
            super.setText(String.format("%.2f", fahrenheit) + " °F");
        } catch (NumberFormatException e) {
            super.setText("Invalid input"); // Handle invalid input
        }
    }
    /*
    Code for testing
    public static void main(String[] args) {
        // create instance of Random class
        Random rand = new Random();
        TempLabel t = new TempLabel();
        final int n = 100;
        for (int i=0; i<n; i++) {
            int j = rand.nextInt(1000);
            t.setText(Integer.toString(j));
            System.out.println("The celsius is "+j+
                    " while the farheneit is "+t.getText());
        }
    }
    */
}
