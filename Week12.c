#include <stdio.h>
#include <stdbool.h>

void print_slots(int slots[], int slotSize) {
    for (int i = 0; i < slotSize; i++) {
        if (slots[i] == -1)
            printf("[ ] ");
        else
            printf("[%d] ", slots[i]);
    }
    printf("\n");
}

int FIFO(int pages[], int n, int slots[], int slotSize) {
    int cur_idx = 0;
    int page_faults = 0;
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        for (int j = 0; j < slotSize; j++) {
            if (slots[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            slots[cur_idx] = page;
            cur_idx = (cur_idx + 1) % slotSize;
            print_slots(slots, slotSize);
            page_faults++;
        }
    }
    return page_faults;
}

int Optimal(int pages[], int n, int slots[], int slotSize) {
    int page_faults = 0;
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        for (int j = 0; j < slotSize; j++) {
            if (slots[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (i < slotSize) {
                slots[i] = page;
            } else {
                int farthest = i + 1;
                int replace_idx = -1;

                for (int j = 0; j < slotSize; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (pages[k] == slots[j]) {
                            if (k > farthest) {
                                farthest = k;
                                replace_idx = j;
                            }
                            break;
                        }
                    }
                    if (k == n) { 
                        replace_idx = j;
                        break;
                    }
                }

                if (replace_idx == -1) {
                    replace_idx = 0;
                }

                slots[replace_idx] = page;
            }
            print_slots(slots, slotSize);
            page_faults++;
        }
    }
    return page_faults;
}

int LRU(int pages[], int n, int slots[], int slotSize) {
    int page_faults = 0;
    int time[slotSize]; 

    for (int i = 0; i < slotSize; i++) {
        time[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;
        int lru_idx = 0;

        for (int j = 0; j < slotSize; j++) {
            if (slots[j] == page) {
                found = true;
                time[j] = i;
                break;
            }
            if (time[j] < time[lru_idx]) {
                lru_idx = j;
            }
        }

        if (!found) {
            slots[lru_idx] = page;
            time[lru_idx] = i;
            print_slots(slots, slotSize);
            page_faults++;
        }
    }
    return page_faults;
}

int LFU(int pages[], int n, int slots[], int slotSize) {
    int page_faults = 0;
    int count[slotSize]; 
    int time[slotSize];
    
    for (int i = 0; i < slotSize; i++) {
        count[i] = 0;
        time[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;
        int lfu_idx = 0;

        for (int j = 0; j < slotSize; j++) {
            if (slots[j] == page) {
                found = true;
                count[j]++;
                time[j] = i;
                break;
            }
            if (count[j] < count[lfu_idx] || (count[j] == count[lfu_idx] && time[j] < time[lfu_idx])) {
                lfu_idx = j;
            }
        }

        if (!found) {
            slots[lfu_idx] = page;
            count[lfu_idx] = 1;
            time[lfu_idx] = i;
            print_slots(slots, slotSize);
            page_faults++;
        }
    }
    return page_faults;
}

int main() {
    int n, slotSize;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter slot size: ");
    scanf("%d", &slotSize);
    int slots[slotSize];

    int ch;
    do {
        int choice;
        printf("Select 1.FIFO 2.Optimal 3.LRU 4.LFU 5.exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        for (int i = 0; i < slotSize; i++) {
            slots[i] = -1;
        }
        int ans;
        switch (choice) {
            case 1:
                ans = FIFO(pages, n, slots, slotSize);
                printf("Total no.of page faults = %d\n", ans);
                break;
            case 2:
                ans = Optimal(pages, n, slots, slotSize);
                printf("Total no.of page faults = %d\n", ans);
                break;
            case 3:
                ans = LRU(pages, n, slots, slotSize);
                printf("Total no.of page faults = %d\n", ans);
                break;
            case 4:
                ans = LFU(pages, n, slots, slotSize);
                printf("Total no.of page faults = %d\n", ans);
                break;
            case 5:
                return 0;
        }
        printf("Do you want to continue (1/0): ");
        scanf("%d", &ch);
    } while (ch == 1);

    return 0;
}
