package com.company;

import java.util.*;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {

        // EX1) Filtrare simplă (fără 'for' clasic)
        // ----------------------------------------
        // Într-un for clasic, am fi scris:
        //   for (int i = 0; i < lista.size(); i++) {
        //       if (lista.get(i).length() > 3) {
        //           listaFiltrata.add(lista.get(i));
        //       }
        //   }

        // Liste de exemplu
        List<String> lista = Arrays.asList("Ana", "Ion", "Maria", "Alin");

        // Înlocuim bucla 'for' cu stream + filter + colectare
        List<String> listaFiltrata = lista.stream()
                .filter(s -> s.length() > 3)
                .collect(Collectors.toList());
        
        System.out.println("EX1 - Strings cu lungime > 3: " + listaFiltrata);


        // EX2) Transformare (map) în loc de for
        // -------------------------------------
        // For clasic:
        //   List<String> upperCaseList = new ArrayList<>();
        //   for (String elem : lista) {
        //       upperCaseList.add(elem.toUpperCase());
        //   }

        // Cu stream:
        List<String> upperCaseList = lista.stream()
                .map(String::toUpperCase) // transformare in uppercase
                .collect(Collectors.toList());
        System.out.println("EX2 - Convertite in UPPER CASE: " + upperCaseList);


        // EX3) Reduce (sumă) pentru o listă de numere
        // -------------------------------------------
        // For clasic:
        //   int sum = 0;
        //   for (int x : numbers) {
        //       sum += x;
        //   }

        List<Integer> numbers = Arrays.asList(10, 20, 30, 40, 50);
        int sum = numbers.stream()
                .reduce(0, (subtotal, element) -> subtotal + element);
        System.out.println("EX3 - Suma numerelor: " + sum);


        // EX4) Filtrare + reduce (produsul numerelor > 5)
        // ----------------------------------------------
        // For clasic:
        //   int product = 1;
        //   for (int i = 0; i < numbers.size(); i++) {
        //       if (numbers.get(i) > 5) {
        //           product *= numbers.get(i);
        //       }
        //   }

        int product = numbers.stream()
                .filter(n -> n > 5)
                .reduce(1, (p, el) -> p * el);
        System.out.println("EX4 - Produsul numerelor > 5: " + product);


        // EX5) Combinare filter + map (în locul unei bucle for care face ambele)
        // ---------------------------------------------------------------------
        // For clasic:
        //   List<Integer> lengths = new ArrayList<>();
        //   for (String s : lista) {
        //       if (s.contains("a")) {
        //           lengths.add(s.length());
        //       }
        //   }

        List<Integer> lengths = lista.stream()
                .filter(s -> s.toLowerCase().contains("a")) // filtrăm doar ce conține 'a'
                .map(String::length)                        // transformăm în lungimea cuvântului
                .collect(Collectors.toList());
        System.out.println("EX5 - Lungimile string-urilor care contin 'a': " + lengths);
    }
}
