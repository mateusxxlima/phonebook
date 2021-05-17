#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EXIT 10

typedef struct contact {
  char name[30];
  char email[40];
  char phone[15];
  struct contact *next;
  struct contact *prev;
} Contact;

typedef struct phoneList {
  Contact *head;
  Contact *tail;
} PhoneList;

Contact *getInputsToAContact() {
  Contact *MContact = malloc(sizeof(Contact));
  printf("\n");
  printf("Nome: ");
  scanf("%s", MContact->name);
  printf("E-mail: ");
  scanf("%s", MContact->email);
  printf("Telefone: ");
  scanf("%s", MContact->phone);
  MContact->next = NULL;
  MContact->prev = NULL;
  return MContact;
}

void listContacts (PhoneList *phoneList) {
  printf("\n### LISTAR CONTATOS ###\n");
  if (phoneList->head == NULL) {
    printf("\n### Nenhum contato para listar! ###\n");
    return;
  }
  Contact *MContact;
  for (MContact = phoneList->head; MContact != NULL; MContact = MContact->next) {
    printf("\nNome: %s\n", MContact->name);
    printf("E-mail: %s\n", MContact->email);
    printf("Telefone: %s\n", MContact->phone);
  }
  return;
}

int areStringsEqual(char str1[], char str2[]) {
  if (strlen(str1) != strlen(str2)) return 0;
  for (int i = 0; i < strlen(str1); i++) {
    if (tolower(str1[i]) != tolower(str2[i])) return 0;
  } 
  return 1;
}

Contact *searchByName(PhoneList *phoneList, char nameToSearch[]) {
  Contact *helper;
  for (helper = phoneList->head; helper != NULL; helper = helper->next) {
    int isEqual = areStringsEqual(helper->name, nameToSearch);
    if (isEqual) return helper;
  }
  return NULL;
}

void queryContact (PhoneList *phoneList) {
  printf("\n### PESQUISAR CONTATO ###\n");
  char nameToSearch[30];
  printf("\nDigite um nome para pesquisar\n");
  printf(": ");
  scanf("%s", nameToSearch);
  Contact *MContact = searchByName(phoneList, nameToSearch);
  if (MContact) {
    printf("\n### Contato encontrado ###\n");
    printf("\nName: %s\n", MContact->name);
    printf("Email: %s\n", MContact->email);
    printf("Phone: %s\n", MContact->phone);
  } else printf("\n### Contato não encontrado ###\n");
  return;
}

void delContact (PhoneList *phoneList) {
  printf("\n### DELETAR CONTATO ###\n");
  char nameToDelete[30];
  printf("\nDigite um nome para deletar: ");
  scanf("%s", nameToDelete);
  Contact *MContact = searchByName(phoneList, nameToDelete);
  if (!MContact) {
    printf("\n### Contato não encontrado! ###\n");
    return;
  }
  if (MContact->prev == NULL) {
    if (MContact->next == NULL) {
      phoneList->head = NULL;
      phoneList->tail = NULL;
    } else {
      phoneList->head = MContact->next;
      phoneList->head->prev = NULL;
    }
  } else {
    MContact->prev->next = MContact->next;
    if (MContact->next) MContact->next->prev = MContact->prev;
    else phoneList->tail = MContact->prev;
  }
  free(MContact);
  printf("\n### Contato deletado com sucesso! ###\n");
  return;
}

int isBigger(char *nameToAdd, char *currentName) {
  int smaller = strlen(nameToAdd) < strlen(currentName) ? strlen(nameToAdd): strlen(currentName);
  for (int i = 0; i < smaller; i++) {
    if (tolower(currentName[i]) > tolower(nameToAdd[i])) return 1;
    if (tolower(currentName[i]) < tolower(nameToAdd[i])) return 0;
  }
  return 0;
}

void insertContactInOrder(Contact *MContact, PhoneList *phoneList) {
  int thisNameIsBigger;
  Contact *helper;
  for (helper = phoneList->head; helper != NULL; helper = helper->next) {
    thisNameIsBigger = isBigger(MContact->name, helper->name);
    if (thisNameIsBigger) {
      if (helper->prev == NULL) {
        phoneList->head = MContact;
        MContact->next = helper;
        helper->prev = MContact;
      } else {
        MContact->next = helper;
        MContact->prev = helper->prev;
        helper->prev = MContact;
        MContact->prev->next = MContact;
      }
      return;
    }
  }
  MContact->prev = phoneList->tail;
  phoneList->tail->next = MContact;
  phoneList->tail = MContact;
  return;
}

void insContact(PhoneList *phoneList) {
  printf("\n### INSERIR CONTATO ###\n");
  Contact *MContact = getInputsToAContact();
  if (phoneList->head == NULL) {
    phoneList->head = MContact;
    phoneList->tail = MContact;
  } else {
    insertContactInOrder(MContact, phoneList);
  }
  printf("\n### Contato inserido com sucesso! ###\n");
  return;
}

int menu() {
  int op;
  printf("\n");
  printf("[1] Inserir contato\n");
  printf("[2] Deletar contato\n");
  printf("[3] Pesquisar contato\n");
  printf("[4] Listar contatos\n");
  printf("[%d] Finalizar\n", EXIT);
  printf(": ");
  scanf("%d", &op);
  return op;
}

void appendContact(PhoneList *phoneList, Contact *contact) {
  if (phoneList->head == NULL) {
    phoneList->head = contact;
    phoneList->tail = contact;
    contact->next = NULL;
    contact->prev = NULL;
  } else {
    contact->prev = phoneList->tail;
    contact->next = NULL;
    phoneList->tail->next = contact;
    phoneList->tail = contact;
  }
  return;
}

PhoneList *getPhoneList() {
  PhoneList *phoneList = malloc(sizeof(PhoneList));
  FILE *file = fopen("phonebook.bin", "rb");
  if (!file) return phoneList;
  Contact *contact;
  while(!feof(file)) {
    contact = malloc(sizeof(Contact));
    fread(contact, sizeof(Contact), 1, file);
    if (strlen(contact->name)) {
      appendContact(phoneList, contact);
    }
  }
  fclose(file);
  return phoneList;
}

void saveToDisk(PhoneList *phoneList) {
  FILE *file = fopen("phonebook.bin", "wb");
  if (!file) {
    printf("Error");
    exit(1);
  }
  Contact *helper;
  for (helper = phoneList->head; helper != NULL; helper = helper->next) {
    fwrite(helper, sizeof(Contact), 1, file);
    free(helper);
  }
  fclose(file);
}

int main() {

  PhoneList *phoneList = getPhoneList();

  int op = 0;
  while (op != EXIT) {
    op = menu();
    switch(op) {
      case 1 : insContact(phoneList);
      break;
      case 2 : delContact(phoneList);
      break;
      case 3 : queryContact(phoneList);
      break;
      case 4 : listContacts(phoneList);
      break;
    }
  }

  saveToDisk(phoneList);
  free(phoneList);

  return 0;
}
