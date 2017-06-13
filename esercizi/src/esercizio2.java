import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

import edu.unito.tree.Tree;

/**
 *  File: esercizio2.java
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 05-05-2017
 *
 */

public class esercizio2 {

  private static String rowRootLabel(String s) {
    if (s == null) return null;
    String[] splitted = s.split(",");
    if (splitted.length > 0) return splitted[0];
    return null;
  }

  private static ArrayList<String> rowChildrenLabel(String s) {
    if (s == null) return null;
    String[] splitted = s.split(",");
    if (splitted.length > 1) {
      ArrayList<String> list = new ArrayList<>(Arrays.asList(splitted));
      list.remove(0);
      return list;
    }
    return null;
  }

  private static Comparator<String> comparator = new Comparator<String>(){
    public int compare(String t1,String t2){
      return t1.compareTo(t2);
    }
  };

  private static Tree<String> load(File file, int max_record_read) {
    Tree<String> tree = null;
    try {
      if (!file.isFile()) throw new FileNotFoundException("File (" + file + ") isn't a file.");

      BufferedReader br = new BufferedReader(new FileReader(file));
      String s;
      int lines = 0;
      boolean limit = true;

      while (limit && (s = br.readLine()) != null) {
        if (max_record_read != -1) {
          limit = lines < max_record_read;
          lines++;
        }

        String rowRootLabel = rowRootLabel(s);
        if (rowRootLabel == null) continue;
        if (tree == null) {
          tree = new Tree<>(rowRootLabel);
          ArrayList<String> rowChildrenLabel = rowChildrenLabel(s);
          if (rowChildrenLabel != null) {
            for (String label : rowChildrenLabel) {
              tree.addTree(new Tree<>(label));
            }
          }
        } else {
          ArrayList<String> rowChildrenLabel = rowChildrenLabel(s);
          if (rowChildrenLabel != null) {
            Tree<String> found = tree.find(rowRootLabel);
            if (found == null)
              throw new Exception("Non so dove aggiungere questo sotto-albero: " + rowRootLabel + "(" + s + ")");
            for (String label : rowChildrenLabel) {
              found.addTree(new Tree<>(label));
            }
          }
        }

      }
    } catch (FileNotFoundException e) {
      e.printStackTrace();
      System.out.println("FileNotFoundException");
      System.exit(1);
    } catch (IOException e) {
      e.printStackTrace();
      System.out.println("IOException");
      System.exit(2);
    } catch (NullPointerException e) {
      e.printStackTrace();
      System.out.println("NullPointerException");
      System.exit(3);
    } catch (Exception e) {
      e.printStackTrace();
      System.exit(4);
    }
    return tree;
  }

  public static void main(String[] args) {
    if (args.length < 1) throw new IllegalArgumentException("NoEnoughArguments");

    String path;
    path = args[0];

    int max_record_read = Integer.MAX_VALUE;
    if (args.length > 1) {
      max_record_read = Integer.parseInt(args[1]);
    }

    Tree<String> tree = load(new File(path), max_record_read);
    System.out.println("Max degree: "+tree.degree());
    System.out.println("Tree is binary: "+tree.isBinary());
    System.out.println("Tree size: "+tree.size());
    System.out.println("Tree depth: "+tree.height());
//    System.out.println(tree);

    System.out.println("\n ******************************\n");

    if (tree != null) {
      Tree<String> BST = tree.toBinarySearchTree(comparator);
      System.out.println("Max degree: "+BST.degree());
      System.out.println("Tree is binary: "+BST.isBinary());
      System.out.println("Tree size: "+BST.size());
      System.out.println("Tree depth: "+BST.height());
//      System.out.println(BST);
    }
  }
}
