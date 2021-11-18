#include "doublylist.h"
#include <stdio.h>

int	main(void)
{
	DoublyList		*lst;
	DoublyListNode	elem;
	int				i;

	lst = createDoublyList();
	i = -1;
	while (++i < 10)
	{
		elem.data = i;
		addDLElement(lst, 0, elem);
	}
	displayDoublyList(lst);
	elem.data = 1000000;
	addDLElement(lst, 10, elem);
	displayDoublyList(lst);
	removeDLElement(lst, 3);
	printf("removed element no.3\n");
	displayDoublyList(lst);
	printf("List length: %d\n", getDoublyListLength(lst));
	removeDLElement(lst, 0);
	printf("removed element no.0\n");
	displayDoublyList(lst);
	printf("List length: %d\n", getDoublyListLength(lst));
	printf("4th element: %d\n", getDLElement(lst, 4)->data);
	clearDoublyList(lst);
	printf("cleared all the list.\n");
	displayDoublyList(lst);
	deleteDoublyList(lst);
}
