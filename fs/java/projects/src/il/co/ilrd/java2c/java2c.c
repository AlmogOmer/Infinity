/*reviewer: Rona */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 40 
typedef struct Object Object_t;
typedef struct Class Class_t;
typedef struct Animal Animal_t;
typedef struct Dog Dog_t;
typedef struct Cat Cat_t;
typedef struct LegendaryAnimal LegendaryAnimal_t;
typedef void* (*vf_t) (void*);

char *ObjectToString(Object_t *this);
void ObjectFinalize(Object_t *this);

void AnimalInitializer();
void AnimalCtor1(Animal_t *this);
void AnimalCtor2(Animal_t *this, int num_masters);
void AnimalsayHello(Animal_t *this);
void AnimalshowCounter();
int AnimalgetNumMasters(Animal_t *this);
char *AnimalToString(Animal_t *this);
void AnimalFinalize(Animal_t *this);

void DogInitializer();
void DogCtor(Dog_t *this);
void DogsayHello(Dog_t *this);
char *DogToString(Dog_t *this);
void DogFinalize(Dog_t *this);

void CatInitializer();
void CatCtor1(Cat_t *this);
void CatCtor2(Cat_t *this, char *colors);
char *CatToString(Cat_t *this);
void CatFinalize(Cat_t *this);

void LegendaryAnimalInitializer();
void LegendaryAnimalCtor(LegendaryAnimal_t *this);
void LegendaryAnimalsayHello(LegendaryAnimal_t *this);
void LegendaryAnimalFinalize(LegendaryAnimal_t *this);
char *LegendaryAnimalToString(LegendaryAnimal_t *this);

static int AnimalCounter = 0;
char str[SIZE];

struct Class{
    char *Name;
    size_t size;
    Class_t *parent;
    vf_t (*VTable)[];
};

struct Object{
    Class_t *mata;
};

vf_t Object_vt[] = {(vf_t)ObjectToString, (vf_t)ObjectFinalize};
Class_t ObjectClass = {"object", sizeof(Object_t), NULL, &Object_vt};

struct Animal{
    Object_t Object;
    int num_legs;
	int num_masters;
	int ID; 
};

vf_t Animal_vt[] = {(vf_t)AnimalToString, (vf_t)AnimalFinalize, (vf_t)AnimalsayHello};
Class_t AnimalClass = {"Animal", sizeof(Animal_t), &ObjectClass, &Animal_vt};

struct Dog{
    Animal_t Animal;
    int num_legs;
};

vf_t Dog_vt[] = {(vf_t)DogToString, (vf_t)DogFinalize,(vf_t)DogsayHello};
Class_t DogClass = {"Dog", sizeof(Dog_t), &AnimalClass, &Dog_vt};

struct Cat{
    Animal_t Animal;
    char colors[SIZE];
    int num_masters;
};

vf_t Cat_vt[] = {(vf_t)CatToString, (vf_t)CatFinalize, (vf_t)AnimalsayHello};
Class_t CatClass = {"Cat", sizeof(Cat_t), &AnimalClass, &Cat_vt};

struct LegendaryAnimal{
    Cat_t Cat;
};

vf_t LegendaryAnimal_vt[] = {(vf_t)LegendaryAnimalToString, (vf_t)LegendaryAnimalFinalize, (vf_t)LegendaryAnimalsayHello};
Class_t LegendaryAnimalClass = {"LegendaryAnimal", sizeof(LegendaryAnimal_t), &CatClass, &LegendaryAnimal_vt};

Object_t *Alloc(Class_t *meta){
    Object_t *ret = (Object_t *)calloc(1, meta->size);
    ret->mata = meta;
    return ret;
}

void AnimalInitializer(){
    static int flag = 0;
    if(flag == 0){
        printf("Static block Animal 1\n");
        printf("Static block Animal 2\n");
        flag = 1;
    }
}

void DogInitializer(){
    static int flag = 0;
    if(flag == 0){
        printf("Static block Dog\n");
        flag = 1;
    }
}

void CatInitializer(){
    static int flag = 0;
    if(flag == 0){
        printf("Static block Cat\n");
        flag = 1;
    }
}

void LegendaryAnimalInitializer(){
    static int flag = 0;
    if(flag == 0){
        printf("Static block Legendary Animal\n");
        flag = 1;
    }
}

char *ObjectToString(Object_t *this){
    snprintf(str, SIZE, "%s@%lu", this->mata->Name, (size_t)this);
	return str;
}

void ObjectFinalize(Object_t *this){
	printf("finalize Object\n");
}

void AnimalCtor1(Animal_t *this){
    AnimalInitializer();
    printf("Instance initialization block Animal\n");
    printf("Animal Ctor\n");
    this->num_legs = 5;
    this->num_masters = 1;
    this->ID = ++AnimalCounter;
    (*this->Object.mata->VTable)[2](this);
    AnimalshowCounter();
	printf("%s\n", (char *)(*this->Object.mata->VTable)[0](this));
	printf("%s\n", ObjectToString((Object_t *)this));
}

void AnimalCtor2(Animal_t *this, int num_masters){
    AnimalInitializer();
    printf("Instance initialization block Animal\n");
    printf("Animal Ctor int\n");
    this->num_legs = 5;
    this->num_masters = num_masters;
    this->ID = ++AnimalCounter;
}

void AnimalsayHello(Animal_t *this){
    printf("Animal Hello!\n");
	printf("I have %d legs\n", this->num_legs);
}

/*static function*/
void AnimalshowCounter(){
	AnimalInitializer();
    printf("%d\n", AnimalCounter);
}

int AnimalgetNumMasters(Animal_t *this){
    return this->num_masters;
}
    
char *AnimalToString(Animal_t *this){
    snprintf(str,SIZE, "Animal with ID: %d", this->ID);
    return str;
}

void AnimalFinalize(Animal_t *this){
	printf("finalize Animal with ID: %d\n" ,this->ID);
    ObjectFinalize((Object_t *)this);
}

void DogCtor(Dog_t *this){
    DogInitializer();
    AnimalCtor2(&this->Animal, 2);
    printf("Instance initialization block Dog\n");
    this->num_legs = 4;
    printf("Dog Ctor\n");
}

void DogsayHello(Dog_t *this){
    printf("Dog Hello!\n");
	printf("I have %d legs\n", this->num_legs);
}

char *DogToString(Dog_t *this){
    snprintf(str,SIZE, "Dog with ID: %d", this->Animal.ID);
    return str;
}

void DogFinalize(Dog_t *this){
	printf("finalize Dog with ID: %d\n" ,this->Animal.ID);
    AnimalFinalize((Animal_t *)this);
}


void CatCtor1(Cat_t *this){
    CatCtor2(this, "black");
    printf("Cat Ctor\n");
    this->num_masters = 2;
}

void CatCtor2(Cat_t *this, char *colors){
    CatInitializer();
    AnimalCtor1(&this->Animal);
    this->num_masters = 5;
    strcpy(this->colors,colors);
    printf("Cat Ctor with color: %s\n" ,colors);
}

char *CatToString(Cat_t *this){
    snprintf(str,SIZE, "Cat with ID: %d", this->Animal.ID);
    return str;
}

void CatFinalize(Cat_t *this){
	printf("finalize Cat with ID: %d\n", this->Animal.ID);
    AnimalFinalize((Animal_t *)this);
}

void LegendaryAnimalCtor(LegendaryAnimal_t *this){
    LegendaryAnimalInitializer();
    CatCtor1(&this->Cat);
    printf("Legendary Ctor\n");
}

void LegendaryAnimalsayHello(LegendaryAnimal_t *this){
    printf("Legendary Hello!\n");
}

void LegendaryAnimalFinalize(LegendaryAnimal_t *this){
	printf("finalize LegendaryAnimal with ID: %d\n", this->Cat.Animal.ID);
    CatFinalize((Cat_t *)this);
}

char *LegendaryAnimalToString(LegendaryAnimal_t *this){
    snprintf(str,SIZE, "LegendaryAnimal with ID: %d", this->Cat.Animal.ID);
    return str;
}

static void foo(Animal_t *a){
	printf("%s\n", (char *)(*a->Object.mata->VTable)[0](a));
}

int main(void){
    int i = 0;
    Animal_t *animal;
    Animal_t *animal1;
    Dog_t *dog;
    Dog_t *dog1;
    Cat_t *cat;
    Cat_t *cat1;
    Cat_t *cat2;
    LegendaryAnimal_t *la;
    LegendaryAnimal_t *la1;

    Animal_t *array[5] = {0};
    
    animal = (Animal_t *)Alloc(&AnimalClass);
    AnimalCtor1(animal);
    
    dog = (Dog_t *)Alloc(&DogClass);
    DogCtor(dog);

    cat = (Cat_t *)Alloc(&CatClass);
    CatCtor1(cat);

    la = (LegendaryAnimal_t *)Alloc(&LegendaryAnimalClass);
    LegendaryAnimalCtor(la);

    AnimalshowCounter();
    printf("%d\n",animal->ID);
    printf("%d\n",dog->Animal.ID);
    printf("%d\n",cat->Animal.ID);
    printf("%d\n",la->Cat.Animal.ID);
    
    dog1 = (Dog_t *)Alloc(&DogClass);
    DogCtor(dog1);

    cat1 = (Cat_t *)Alloc(&CatClass);
    CatCtor1(cat1);

    cat2 = (Cat_t *)Alloc(&CatClass);
    CatCtor2(cat2, "white");

    la1 = (LegendaryAnimal_t *)Alloc(&LegendaryAnimalClass);
    LegendaryAnimalCtor(la1);

    animal1 = (Animal_t *)Alloc(&AnimalClass);
    AnimalCtor1(animal1);

    array[0] = (Animal_t *)dog1;
    array[1] = (Animal_t *)cat1;
    array[2] = (Animal_t *)cat2;
    array[3] = (Animal_t *)la1;
    array[4] = (Animal_t *)animal1;

    for (i = 0; i < 5; ++i){
        (*array[i]->Object.mata->VTable)[2](array[i]);
        printf("%d\n",AnimalgetNumMasters(array[i]));
    }

    for (i = 0; i < 5; ++i){
        foo(array[i]);
    }

    return 0;
}


