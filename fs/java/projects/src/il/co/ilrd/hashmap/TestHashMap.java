package il.co.ilrd.hashmap;

public class TestHashMap {
    public static void main(String[] args) {
        HashMap<Integer,String> myhash = new HashMap<>(20);
        if (!myhash.isEmpty()){
            System.out.println("failed in isempty1");
        }

        if(myhash.size() != 0){
            System.out.println("failed in size1");
        }

        myhash.put(10, "almog");
        myhash.put(20, "andrey");
        myhash.put(30, "omer");

        if (myhash.isEmpty()){
            System.out.println("failed in isempty2");
        }

        if(myhash.size() != 3){
            System.out.println("failed in size2");
        }

        myhash.clear();

        if (!myhash.isEmpty()){
            System.out.println("failed in isempty3");
        }

        if(myhash.size() != 0){
            System.out.println("failed in size3");
        }

        myhash.put(10, "almog");
        myhash.put(20, "andrey");
        myhash.put(30, "omer");
        myhash.put(40, "idan");
        myhash.put(50, "maya");
        myhash.put(60, "eden");
        myhash.put(70, "shir");
        myhash.put(80, "hila");

        if(myhash.size() != 8){
            System.out.println("failed in size4");
        }

        if(!myhash.containsKey(50)){
            System.out.println("failed in containsKey1");
        }

        if(!myhash.containsValue("almog")){
            System.out.println("failed in containsValue1");
        }

        if(myhash.remove(80) != "hila" ){
            System.out.println("failed in remove1");
        }

        if(myhash.size() != 7){
            System.out.println("failed in size5");
        }

        if(myhash.containsKey(80)){
            System.out.println("failed in containsKey2");
        }

        if(myhash.containsValue("hila")){
            System.out.println("failed in containsValue2");
        }

        if(myhash.put(10, "almog2") != "almog"){
            System.out.println("failed in put");
        }

        if(myhash.get(10) != "almog2"){
            System.out.println("failed in get1");
        }
        if(myhash.get(20) != "andrey"){
            System.out.println("failed in get2");
        }
        if(myhash.get(30) != "omer"){
            System.out.println("failed in get3");
        }
        if(myhash.get(40) != "idan"){
            System.out.println("failed in get4");
        }
        
        if(myhash.get(50) != "maya"){
            System.out.println("failed in get5");
        }

        if(myhash.get(60) != "eden"){
            System.out.println("failed in get6");
        }

        if(myhash.get(70) != "shir"){
            System.out.println("failed in get7");
        }

        if(myhash.get(80) != null){
            System.out.println("failed in get8");
        }

        System.out.println("test done!");
    }
}
