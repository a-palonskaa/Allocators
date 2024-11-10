LIST_DIR = free_list_allocator_test
POOL_DIR = pool_allocator_testing
LINEAR_DIR = linear_allocator_testing
STACK_DIR = stack_allocator_test
CALLOC_DIR = calloc_test
SUBDIRS = $(LIST_DIR) $(POOL_DIR) $(LINEAR_DIR) $(STACK_DIR) $(CALLOC_DIR)

all: list pool linear stack calloc

list:
	@for dir in $(LIST_DIR); do \
		$(MAKE) -C $$dir all;   \
	done

pool:
	@for dir in $(POOL_DIR); do \
		$(MAKE) -C $$dir all;   \
	done

linear:
	@for dir in $(LINEAR_DIR); do \
		$(MAKE) -C $$dir all;     \
	done

stack:
	@for dir in $(STACK_DIR); do \
		$(MAKE) -C $$dir all;    \
	done

calloc:
	@for dir in $(CALLOC_DIR); do \
		$(MAKE) -C $$dir all;     \
	done

clean:
	@for dir in $(SUBDIRS); do  \
		$(MAKE) -C $$dir clean; \
	done
