import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import edu.unito.tree.Tree;

/**
 *  File: esercizio2.java
 *  Author: Riccardo Ferrero Regis, Roger Ferrod, Luca Chironna
 *
 *  Date: 05-05-2017
 *
 */

public class esercizio2 {
  private static Tree<String> rowToTree(String row) {
    String[] splitted = s.split(",");
    if (tree == null)
      tree = new Tree<>(splitted[0]);
    Tree<String> root = new Tree<>(splitted[0]);
    for (int i = 1; i < splitted.length; i++) {
      root.addTree(new Tree<>(splitted[i]));
    }
    System.out.println(root);
  }
  public static void main(String[] args) {
    if (args.length < 1) throw new IllegalArgumentException("NoEnoughArguments");

    String path = args[0];
    try {
      BufferedReader br = new BufferedReader(new FileReader(path));
      String s;
      Tree<String> tree = null;
      int lines=0;
      while((s = br.readLine()) != null && lines < 2) {
        Tree<String> subtree = rowToTree(s);
        if (subtree != null) {
          tree.addTree(subtree);
        }

        System.out.println(lines);
        lines++;
      }
      System.out.println(tree.toString());
    } catch (IOException e) {
      e.printStackTrace();
    } catch (NullPointerException e) {
      e.printStackTrace();
      System.out.println("nullpointerexception");
    }

  }
}
