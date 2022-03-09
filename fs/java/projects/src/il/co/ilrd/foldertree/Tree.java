/*Reviewer : Shani*/
package il.co.ilrd.foldertree;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class Tree{
    
    private Folder rootDirectory;

    public Tree(String path){
        File root = new File(path);
        if (root.isDirectory()){
            rootDirectory = new Folder(root);
        }
        else{
            System.out.println(root.getName() + " [error opening dir]");
        }
        
    }

    public void print(){
        if(rootDirectory != null){
            rootDirectory.print(0);
        } 
    }

    interface AbstractFile{
        abstract void print(int offset);
    }

    private class LeafFile implements AbstractFile{
        private String fileName;

        public LeafFile(File pathSub){
            fileName = pathSub.getName();
        }

        @Override
        public void print(int offset){
            printOffset(offset);
            System.out.println("|____" + fileName);
            ++offset;
        }
    }

    private class Folder implements AbstractFile{
        private List<AbstractFile> listFile = new ArrayList<>();
        private String folderName;

        public Folder(File root){ 
            folderName = root.getName();  
            File [] subfiles = root.listFiles();  
            for (File pathSub : subfiles) {
                if (pathSub.isDirectory()){
                    listFile.add(new Folder(pathSub));
                }
                else{
                    listFile.add(new LeafFile(pathSub));
                }
            }
        
        }

        @Override
        public void print(int offset){
            printOffset(offset);
            System.out.println("|___" + folderName);
            ++offset;

            for (AbstractFile abstractFile : listFile) {
                abstractFile.print(offset);
            }
        }
    }

    private void printOffset(int offset) {
        for (int i = 0; i < offset; ++i) {
            System.out.print("   ");
        }
    }

    public static void main(String[] args) {
        Tree tree = new Tree("./co");
        tree.print();
    }

}