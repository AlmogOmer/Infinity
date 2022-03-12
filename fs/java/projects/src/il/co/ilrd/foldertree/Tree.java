/*Reviewer : Shani*/
package il.co.ilrd.foldertree;

import java.io.File;
import java.security.InvalidParameterException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import il.co.ilrd.factory.Factory; 

public class Tree{
    
    private Folder rootDirectory;
    private int folderCounter = 0;
    private int fileCounter = 0;

    private Factory<AbstractFile, File, String> treeFactory = new Factory<>();

    public Tree(String path){
        Objects.requireNonNull(path);

        treeFactory.add("Folder", Folder :: new);
        treeFactory.add("File", LeafFile :: new);

        File root = new File(path);
        if(!root.exists()){
            throw new InvalidParameterException("invalid path");
        }

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
            System.out.println(folderCounter + " directoried " + fileCounter + " files");
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
            if(subfiles.length != 0){
                for (File pathSub : subfiles) {
                    if (pathSub.isDirectory()){
                        ++folderCounter;
                        listFile.add(treeFactory.create("Folder", pathSub));
                    }
                    else{
                        ++fileCounter;
                        listFile.add(treeFactory.create("File", pathSub));
                    }
                }
            }
        
        }

        @Override
        public void print(int offset){
            printOffset(offset);
            if (offset == 0){
                System.out.println(folderName);
            }
            else{
                System.out.println("|____" + folderName);
            }
            
            ++offset;
            for (AbstractFile abstractFile : listFile) {
                abstractFile.print(offset);
            }
        }
    }

    private void printOffset(int offset) {
        for (int i = 0; i < offset-1; ++i) {
            System.out.print("   ");
        }
    }

    public static void main(String[] args) {
        Tree tree = new Tree(".");
        tree.print();
    }

}