package il.co.ilrd.composite;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class Tree{
    
    Folder rootDirectory;

    public Tree(String path){
        rootDirectory = new Folder(path);
    }

    public void print(){
        rootDirectory.print();
    }

    interface AbstractFile{
        abstract void print();
    }

    private class LeafFile implements AbstractFile{
        private String fileName;

        public LeafFile(String fileName){
            this.fileName = fileName;
        }

        @Override
        public void print(){
            System.out.println(fileName);
        }
    }

    private class Folder implements AbstractFile{
        private List<AbstractFile> listFile = new ArrayList<>();
        private String folderName;

        public Folder(String path){
            folderName = path;
            File root = new File(path);        
            File [] subfiles = root.listFiles();  
            for (File pathSub : subfiles) {
                if (root.isDirectory()){
                    listFile.add(new Folder(pathSub.getName()));
                }
                else{
                    listFile.add(new LeafFile(pathSub.getName()));
                }
            }
            
        }

        @Override
        public void print(){
            System.out.println(folderName);
            for (AbstractFile abstractFile : listFile) {
                abstractFile.print();
            }
        }
    }

    public static void main(String[] args) {
        String path = "~/Desktop/infinity/almog-pmer/fs";
        Tree tree = new Tree(path);
        tree.print();
    }

}