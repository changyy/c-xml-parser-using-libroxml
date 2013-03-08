#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <roxml.h>

#define BUF_SIZE 1024
#define XML_TEST_DATA "\
<xml>\
	<item>\
		<field1>value 1</field1>\
		<field2>value 2</field2>\
	</item>\
	<item>\
		<field1>value 3</field1>\
		<field2>value 4</field2>\
	</item>\
</xml>\
"

void get_item_info(node_t *node) {
	const int buf_size = BUF_SIZE;
	char buf[BUF_SIZE+1];
	int read_size;
	node_t *tmp;

	if( node == NULL )
		return;

	if( (tmp = roxml_get_nodes( node, ROXML_ELM_NODE, "field1" , 0) ) != NULL ) {
		read_size = 0;
		printf( "key: %s\tvalue: %s\n", roxml_get_name(tmp, NULL, 0), roxml_get_content(tmp, buf, buf_size, &read_size) );
	}

	if( (tmp = roxml_get_nodes( node, ROXML_ELM_NODE, "field2" , 0) ) != NULL ) {
		read_size = 0;
		printf( "key: %s\tvalue: %s\n", roxml_get_name(tmp, NULL, 0), roxml_get_content(tmp, buf, buf_size, &read_size) );
	}
}

int main(int argc, char *argv[]) {
	node_t *root, *node, *item;
	int item_count;
	if( (root = roxml_load_buf(XML_TEST_DATA)) != NULL ) {
		printf("root != NULL:%s\n", roxml_get_name(root, NULL, 0));
		//node = roxml_get_chld( root, NULL, 0);	// xml
		//node = roxml_get_chld( node, NULL, 0);	// item
		node = roxml_get_nodes( root, ROXML_ALL_NODE, "xml" , 0);
		item_count = 0;
		if( (item = roxml_get_nodes( node, ROXML_ALL_NODE, "item" , item_count) ) != NULL ) {
			printf("Get %s [%d]\n", roxml_get_name(item, NULL, 0), ++item_count);
			while( (item = roxml_get_next_sibling( item )) != NULL ) {
				printf("Get %s [%d]\n", roxml_get_name(item, NULL, 0), ++item_count);
				get_item_info(item);
			}
		}
		roxml_close(root);
	}
	return 0;
}

