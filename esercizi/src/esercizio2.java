import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

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

  public static void main(String[] args) {
    if (args.length < 1) throw new IllegalArgumentException("NoEnoughArguments");

    String path = args[0];

    int max_lines = Integer.MAX_VALUE;
    if (args.length > 1) {
      max_lines = Integer.parseInt(args[1]);
    }

    try {
      File file = new File(path);
      if (!file.isFile()) throw new FileNotFoundException("File ("+path+") is't a file.");

      BufferedReader br = new BufferedReader(new FileReader(file));
      String s;
      Tree<String> tree = null;
      int lines=0;
      while(lines < max_lines && (s = br.readLine()) != null) {
        lines++;
        System.out.println("Line: " + lines +":\t" + s);

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
            if (found == null) throw new Exception("Non so dove aggiungere questo sotto-albero: "+rowRootLabel + "("+s+")");
            for (String label : rowChildrenLabel) {
              found.addTree(new Tree<>(label));
            }
          }
        }
        System.out.println(tree.toString());
      }
    } catch (FileNotFoundException e) {
      e.printStackTrace();
      System.out.println("FileNotFoundException");
    } catch (IOException e) {
      e.printStackTrace();
      System.out.println("IOException");
    } catch (NullPointerException e) {
      e.printStackTrace();
      System.out.println("NullPointerException");
    } catch (Exception e) {
      e.printStackTrace();
    }

  }
}
