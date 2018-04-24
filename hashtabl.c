#include <linux/module.h> // Needed for all modules
#include <linux/init.h>	  // Needed for macros
#include <linux/types.h>   // Needed for list macros
#include <linux/kernel.h>  // Needed for KERN_INFO
#include <linux/list.h>    // Needed for linked list
#include <linux/types.h>   // Needed for list macros
#include <linux/slab.h>    // Needed for kernel
//#include <linux/hashtable.h> // Needed for hashtable

//#define NUM_OF_BIRTHDAYS 5
#define TABLE_SIZE 5

// Birthday struct
struct birthday {
	char name[100];
	int day;
	int month;
	int year;
	struct list_head my_hash_list;
};


struct bucket {
	struct list_head bucket_list; // list_head for each bucket
	unsigned int key;
	birthday* value;
};


static void birthday_hash_add(char birthday[]) {
	int i = 0;
	int alp = 0;

	while (birthday[i] != '\0') {
		alp += (int) birthday[i];
		i++;
	}
	return alp%5;
//	unsigned int hashind = name_hash(b.name);
//	hlist_add_head(&b.my_hash_list, &(birthday_table.list_head[hashind]));
}



LIST_HEAD(birthday_list);
LIST_HEAD(bucket_glb);
LIST_HEAD(bucket_list_tbl);

static int birthday_hash_init (void) {
	
	printk(KERN_INFO "Loading Module \n");

	char persons[TABLE_SIZE][100];
	strcpy(persons[0], "Ashim");
	strcpy(persons[1], "Abdulla");
	strcpy(persons[2], "Babloo");
	strcpy(persons[3], "Pyakurel");
	strcpy(persons[4], "Asish");

	birthday *person;
	bucket *buk;
	unsigned int i, hs;
	for (i = 0; i < TABLE_SIZE; i++) {
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = i + 12;
		person->month = i + 3;
		person->year = i + 2000;
		strcpy(person->name, persons[i]);
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);
	}
	birthday birth[TABLE_SIZE];
	birthday *head;
	bucket *buckethead;
	i = 0;
	list_for_each_entry(head, &birthday_list, list) {
		birth[i].day = head->day;
		birth[i].month = head->month;
		birth[i].year = head->year;
		strcpy(birth[i].name, persons[i]);
		printk(KERN_INFO "Day: %d, Month: %d, Year: %d", head->day, head->month, head->year);
		i++;
	}

	for(i = 0; i < TABLE_SIZE; i++) {
		bck = kmalloc(sizeof(*bck), GFP_KERNEL);
		bck->key = i +1;
		bck->value = NULL;
		INIT_LIST_HEAD(&bck->bucket_list);
		list_add_tail(&bck->bucket_list, &bucket_glb);
	}

	i = 0;
	list_for_each_entry(head, &birthday_list, list) {
		printk(KERN_INFO "Name: %s, Day: %d, Month: %d, Year: %d\n", head->name, head->day, head->month, head->year);
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		strcpy(person->name, birth[i].name);
		person->day = birth[i].day;
		person->month = birth[i].month;
		person->year = birth[i].year;
		INIT_LIST_HEAD(&person->list);

		hs = birthday_hash_add(head->name);
		list_for_each_entry(buk, &bucket_glb, bucket_list) {
			if(buk->key == hs && buk->value != NULL) {
				list_add_tail(&person->list, &buk->value->list);
			}
			if(buk->key == hs && buk->value == NULL) {
				buk->value = person;
			}
		}
		i++;
	}

	i = 0;
	birthday *ptk;

	list_for_each_entry(buk, &bucket_glb, bucket_list) {
		if (buk -> value != NULL) {
			bucket_list_tbl = buk->value->list;
			struct list_head* tmp;
			list_for_each(tmp, &(bucket_list_tbl)) {
				birthday *tp = list_entry(tmp, birthday, list);
				printk("Name: %s, Day: %d, Month: %d, Year: %d", tp->name, tp->day, tp->month, tp->year);
			}
		}
	}


	return 0;
}

static void birthday_hash_clean(void) {
	//kfree(birthday_table.list_head);
	printk(KERN_INFO "Removing module\n");
	birthday *head_, *next;
	list_for_each_entry_safe(head_, next, &birthday_list, list) {
		printk(KERN_INFO "Removing items: Day %d, Month %d, Year %d \n", head_->day, head_->month, head_->year);
		list_del(&head_->list);
		kfree(head_);
	}
}

// Macros for registering module entry and exit points
module_init(birthday_hash_init);
module_exit(birthday_hash_clean);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module for Hashtable");
MODULE_AUTHOR("Ram D");
