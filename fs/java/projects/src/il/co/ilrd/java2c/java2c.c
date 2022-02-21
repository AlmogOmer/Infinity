#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Object Object_t;
typedef struct Class Class_t;
typedef struct Animal Animal_t;
typedef struct Dog Dog_t;
typedef struct Cat Cat_t;
typedef struct LegendaryAnimal LegendaryAnimal_t;
typedef void (*vf_t) (void*);

char *ObjectToString(Object_t *this);
void ObjectFinalize(Object_t *this);

void AnimalCtor1(Animal_t *this);
void AnimalCtor2(Animal_t *this, int num_masters);
void AnimalsayHello(Animal_t *this);
void AnimalshowCounter(Animal_t *this);
void AnimalgetNumMasters(Animal_t *this);
char *AnimalToString(Animal_t *this);
void AnimalFinalize(Animal_t *this);

void DogCtor(Dog_t *this);
void DogsayHello(Dog_t *this);
char *DogToString(Dog_t *this);
void DogFinalize(Dog_t *this);

void CatCtor1(Cat_t *this);
void CatCtor2(Cat_t *this, char *colors);
char *CatToString(Cat_t *this);
void CatFinalize(Cat_t *this);

void LegendaryAnimalCtor(LegendaryAnimal_t *this);
void LegendaryAnimalsayHello(LegendaryAnimal_t *this);
void LegendaryAnimalFinalize(LegendaryAnimal_t *this);
char *LegendaryAnimalToString(LegendaryAnimal_t *this);

static int AnimalCounter = 0;

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

vf_t Animal_vt[] = {(vf_t)AnimalToString, (vf_t)AnimalFinalize, (vf_t)AnimalsayHello, (vf_t)AnimalshowCounter, (vf_t)AnimalgetNumMasters};
Class_t AnimalClass = {"Animal", sizeof(Animal_t), &ObjectClass, &Animal_vt};

struct Dog{
    Animal_t Animal;
};

vf_t Dog_vt[] = {(vf_t)DogToString, (vf_t)DogFinalize,(vf_t)DogsayHello, (vf_t)AnimalshowCounter, (vf_t)AnimalgetNumMasters};
Class_t DogClass = {"Dog", sizeof(Dog_t), &AnimalClass, &Dog_vt};

struct Cat{
    Animal_t Animal;
    char *colors;
};

vf_t Cat_vt[] = {(vf_t)CatToString, (vf_t)CatFinalize, (vf_t)AnimalsayHello, (vf_t)AnimalshowCounter, (vf_t)AnimalgetNumMasters};
Class_t CatClass = {"Cat", sizeof(Cat_t), &AnimalClass, &Cat_vt};

struct LegendaryAnimal{
    Cat_t Cat;
};

vf_t LegendaryAnimal_vt[] = {(vf_t)LegendaryAnimalToString, (vf_t)LegendaryAnimalFinalize, (vf_t)LegendaryAnimalsayHello, (vf_t)AnimalshowCounter, (vf_t)AnimalgetNumMasters};
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

    printf("Instance initialization block Animal\n");
}

void DogInitializer(){
    static int flag = 0;
    if(flag == 0){
        printf("Static block Dog\n");
        flag = 1;
    }

    printf("Instance initialization block Dog\n");
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
    return this->mata->Name;
}

void ObjectFinalize(Object_t *this){
	printf("finalize Object\n");
}

void AnimalCtor1(Animal_t *this){
    AnimalInitializer();
    printf("Animal Ctor\n");
    this->num_legs = 5;
    this->num_masters = 1;
    this->ID = ++AnimalCounter;
    (*this->Object.mata->VTable)[2](this);
    (*this->Object.mata->VTable)[3](this);
	//printf("%s\n", (char *)(*this->Object.mata->VTable)[0](this));
	//printf("%s\n", (char *)(*this->Object.mata->parent->VTable)[0](this));
}

void AnimalCtor2(Animal_t *this, int num_masters){
    AnimalInitializer();
    printf("Animal Ctor int\n");
    this->num_legs = 5;
    this->num_masters = num_masters;
    this->ID = ++AnimalCounter;
}

void AnimalsayHello(Animal_t *this){
    printf("Animal Hello!\n");
	printf("I have %d legs\n", this->num_legs);
}

void AnimalshowCounter(Animal_t *this){
	printf("%d\n", AnimalCounter);
}

void AnimalgetNumMasters(Animal_t *this){
	printf("%d\n", this->num_masters);
}

char *AnimalToString(Animal_t *this){
    static char str[50];
    sprintf(str, "Animal with ID: %d\n", this->ID);
    return str;
}

void AnimalFinalize(Animal_t *this){
	printf("finalize Animal with ID: %d\n" ,this->ID);
    (*this->Object.mata->parent->VTable)[1](this);
}

void DogCtor(Dog_t *this){
    AnimalCtor2(&this->Animal, 2);
    DogInitializer();
    this->Animal.num_legs = 4;
    printf("Dog Ctor\n");
}

void DogsayHello(Dog_t *this){
    printf("Dog Hello!\n");
	printf("I have %d legs\n", this->Animal.num_legs);
}

char *DogToString(Dog_t *this){
    static char str[50];
    sprintf(str, "Dog with ID: %d\n", this->Animal.ID);
    return str;
}

void DogFinalize(Dog_t *this){
	printf("finalize Dog with ID: %d\n" ,this->Animal.ID);
    (*this->Animal.Object.mata->parent->VTable)[1](this);
}


void CatCtor1(Cat_t *this){
    AnimalCtor1(&this->Animal);
    CatInitializer();
    CatCtor2(this, "black");
    printf("Cat Ctor\n");
    this->Animal.num_masters = 2;
}

void CatCtor2(Cat_t *this, char *colors){
    AnimalCtor1(&this->Animal);
    CatInitializer();
    this->colors = colors;
    this->Animal.num_masters = 5;
    printf("Cat Ctor with color: %s\n" ,colors);
}

char *CatToString(Cat_t *this){
    static char str[50];
    sprintf(str, "Cat with ID: %d\n", this->Animal.ID);
    return str;
}

void CatFinalize(Cat_t *this){
	printf("finalize Cat with ID: %d\n", this->Animal.ID);
    (*this->Animal.Object.mata->parent->VTable)[1](this);
}

void LegendaryAnimalCtor(LegendaryAnimal_t *this){
    CatCtor1(&this->Cat);
    LegendaryAnimalInitializer();
    printf("Legendary Ctor\n");
}

void LegendaryAnimalsayHello(LegendaryAnimal_t *this){
    printf("Legendary Hello!\n");
}

void LegendaryAnimalFinalize(LegendaryAnimal_t *this){
	printf("finalize LegendaryAnimal with ID: %d\n", this->Cat.Animal.ID);
    (*this->Cat.Animal.Object.mata->parent->VTable)[1](this);
}

char *LegendaryAnimalToString(LegendaryAnimal_t *this){
    static char str[50];
    sprintf(str, "LegendaryAnimal with ID: %d\n", this->Cat.Animal.ID);
    return str;
}


int main(void){
    Object_t *animal;
    Object_t *dog;
    Object_t *cat;
    Object_t *LegendaryAnimal;
    animal = Alloc(&AnimalClass);
    AnimalCtor1((Animal_t *)animal);
    dog = Alloc(&DogClass);
    DogCtor((Dog_t *)dog);
    cat = Alloc(&CatClass);
    CatCtor1((Cat_t *)cat);
    LegendaryAnimal = Alloc(&LegendaryAnimalClass);
    LegendaryAnimalCtor((LegendaryAnimal_t *)LegendaryAnimal);

    return 0;
}


