package il.co.ilrd.foldertree;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class Tree{
    
    Folder rootDirectory;

    public Tree(String path){
        rootDirectory = new Folder(path);
    }

    public void print(){
        rootDirectory.print(0);
    }

    interface AbstractFile{
        abstract void print(int offset);
    }

    private class LeafFile implements AbstractFile{
        private String fileName;

        public LeafFile(String fileName){
            this.fileName = fileName;
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

        public Folder(String path){ 
            File root = new File(path);
            folderName = root.getName();  
            File [] subfiles = root.listFiles();  
            for (File pathSub : subfiles) {
                if (pathSub.isDirectory()){
                    listFile.add(new Folder(pathSub.toString()));
                }
                else{
                    listFile.add(new LeafFile(pathSub.getName()));
                }
            }
            
        }

        @Override
        public void print(int offset){
            printOffset(offset);
            System.out.println("|__" + folderName);
            ++offset;

            for (AbstractFile abstractFile : listFile) {
                abstractFile.print(offset);
            }
        }
    }

    public void printOffset(int offset) {
        for (int i = 0; i < offset; ++i) {
            System.out.print("   ");
        }
    }

    public static void main(String[] args) {
        Tree tree = new Tree(".");
        tree.print();
    }

}