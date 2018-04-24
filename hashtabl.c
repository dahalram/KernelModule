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



/*
struct HashTable {
	unsigned int size;
	struct hlist_head *list_head;
};

static struct HashTable birthday_table;

unsigned int name_hash(const char *str) {
	int ch;
	unsigned long hash = 0;
	while ((ch == *str++)) {
		hash = (hash << 8) + ch;
	}
	return hash % birthday_table.size;
}

static void traverse_ht(void) {
	struct hlist_node *h1;
	unsigned int i;
	for (i = 0; i < birthday_table.size; i++) {
		hlist_for_each(h1, &(birthday_table.list_head[i])) {
			struct birthday *b = hlist_entry(h1, struct birthday, my_hash_list);
			printk("Name:%s, day:%d, month:%d, year:%d is in bucket %d", b->name, b->day, b->month, b->year, i);
		}
	}
}

struct birthday *set_name_as_key(const char *key) {
	unsigned int hashind = name_hash(key);
	struct hlist_node *h1;
	hlist_for_each(h1, &(birthday_table.list_head[hashind])) {
		struct birthday *b = hlist_entry(h1, struct birthday, my_hash_list);
		if (!strncmp(b->name, key, 101)) 
			return b;
	}
	return NULL;
}

static void make_new_table(unsigned int n) {
	struct hlist_head *h1;
	h1 = kmalloc(sizeof(*h1) * n, GFP_KERNEL);
	unsigned int i;
	if (h1 != NULL) {
		for (i = 0; i < n; i++) {
			INIT_HLIST_HEAD(&h1[i]);
		}
	}
	birthday_table.list_head = h1;
	birthday_table.size = n;
}
*/
/*#define HASH_TABLE(birthday_hash, BITS)\
	struct hlist_head birthday_hash[1 << (BITS)] =\ 
		{ [0 ... ((1 << (BITS)) -1)] = HLIST_HEAD_INIT}
*/
//DEFINE_HASHTABLE(a, BITS);

/*
#define hash_add_rcu(hashtable, node, key)\
	hlist_add_head_rcu(node, &hashtable[hash_min(key, HASH_BITS(hashtable))])

*/

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

struct birthday first = {
	.name = "abcd",
	.day = 1,
	.month = 12,
	.year = 1990,
	//.my_hash_list = 0
};

struct birthday second = {
	.name = "abcde",
	.day = 15,
	.month = 12,
	.year = 1995,
	//.my_hash_list = 0
};

struct birthday third = {
	.name = "abcd",
	.day = 12,
	.month = 12,
	.year = 1990,
	//.my_hash_list = 0
};

struct birthday fourth = {
	.name = "abcdef",
	.day = 15,
	.month = 1,
	.year = 1996,
	//.my_hash_list = 0
};

struct birthday fifth = {
	.name = "abcdef",
	.day = 21,
	.month = 2,
	.year = 1990,
	//.my_hash_list = 0
};

LIST_HEAD(birthday_list);
LIST_HEAD(bucket_glb);
LIST_HEAD(bucket_list_tbl);

static int birthday_hash_init (void) {
	/*struct birthday *first, *second, *third, *fourth, *fifth, *tmp;

	first = kmalloc(sizeof *first, GFP_KERNEL);
	if (!first) { printk("can't allocate memory"); return -ENOMEM; }

	second = kmalloc(sizeof *second, GFP_KERNEL);
	third = kmalloc(sizeof *third, GFP_KERNEL);
	fourth = kmalloc(sizeof *fourth, GFP_KERNEL);
	fifth = kmalloc(sizeof *fifth, GFP_KERNEL);

	//memcpy(first->name, "a", 1);
	first->name = "a";
	first->day = 1;
	first->month = 1;
	first->year = 2001;

	//memcpy(second->name, "ba", 2);
	second->name = "ba";
	second->day = 2;
	second->month = 2;
	second->year = 2002;

	//memcpy(third->name, "cbc", 3);
	third->name = "cba";
	third->day = 3;
	third->month = 3;
	third->year = 2003;

	//memcpy(fourth->name, "dbcd", 4);
	fourth->name = "dcba";	
	fourth->day = 4;
	fourth->month = 4;
	fourth->year = 2004;

	//memcpy(fifth->name, "ebcde", 5);
	fifth->name = "edcba";
	fifth->day = 5;
	fifth->month = 5;
	fifth->year = 2005; */
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
		bck->id = i +1;
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
			if(buk->id == hs && buk->value != NULL) {
				list_add_tail(&person->list, &buk->value->list);
			}
			if(buk->id == hs && buk->value == NULL) {
				buk->value = person;
			}
		}
		i++;
	}

	i = 0;
	birthday *ptk;

	list_for_each_entry(buk, &bucket_glb, bucket_list) {
		
	}
	make_new_table(n);

	birthday_hash_add(first);
	birthday_hash_add(second);
	birthday_hash_add(third);
	birthday_hash_add(fourth);
	birthday_hash_add(fifth);

	traverse_ht();

	/*int i = 0;

	hash_for_each(a, i, tmp, my_hash_list) {
		printk(KERN_INFO "name=%s is in bucket %d\n", first->name, i);
	}*/

	return 0;
}

static void birthday_hash_clean(void) {
	//kfree(birthday_table.list_head);
	printk(KERN_INFO "Removing module\n");
	birthday *head_, *next;
	list_for_each_entry_safe(head_, next, &birthday_list, list) {
		printk(KERN_INFO "Removing items: day %d, month %d, year %d \n", head_->day, head_->month, head_->year);
		list_del(&head_->list);
		kfree(ptr);
	}
}

// Macros for registering module entry and exit points
module_init(birthday_hash_init);
module_exit(birthday_hash_clean);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module for Hashtable");
MODULE_AUTHOR("Ram D");
