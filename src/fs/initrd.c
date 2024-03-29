#include <kheap.h>
#include <string.h>
#include <fs/initrd.h>

initrd_header_t *initrd_head;
initrd_file_t *fhead;

fs_node_t *initrd_root;
fs_node_t *initrd_dev;
fs_node_t *root_nodes;

int nroot_nodes;

struct dirent dirent;

static u32 initrd_read(fs_node_t *node, u32 off, u32 size, u8 *buff) {
    initrd_file_t head = fhead[node->inode];
    if (off > head.len) {
        return 0;
    }
    if (off + size > head.len) {
        size = head.len - off;
    }
    memcpy(buff, (u8 *) (head.off + off), size);
    return size;
}

static struct dirent *initrd_readdir(fs_node_t *node, u32 index) {
    if (node == initrd_root && index == 0) {
        strcpy(dirent.name, "dev");
        dirent.name[3] = 0;
        dirent.ino = 0;
        return &dirent;
    }

    if (index - 1 >= nroot_nodes) {
        return 0;
    }
    strcpy(dirent.name, root_nodes[index - 1].name);
    dirent.name[strlen(root_nodes[index - 1].name)] = 0;
    dirent.ino = root_nodes[index - 1].inode;
    return &dirent;
}

static fs_node_t *initrd_finddir(fs_node_t *node, char *name) {
    if (node == initrd_root && strcmp(name, "dev")) {
        return initrd_dev;
    }

    for (int i = 0; i < nroot_nodes; i++) {
        if (strcmp(name, root_nodes[i].name)) {
            return &root_nodes[i];
        }
    }
    return 0;
}

fs_node_t *init_initrd(u32 loc) {
    initrd_head = (initrd_header_t *) loc;
    fhead = (initrd_file_t *) (loc + sizeof(initrd_header_t));

    initrd_root = (fs_node_t *) kmalloc(sizeof(fs_node_t));
    strcpy(initrd_root->name, "initrd");
    initrd_root->mask = initrd_root->uid = initrd_root->gid = initrd_root->inode = initrd_root->len = 0;
    initrd_root->flags = FS_DIR;
    initrd_root->read = 0;
    initrd_root->write = 0;
    initrd_root->open = 0;
    initrd_root->close = 0;
    initrd_root->readdir = &initrd_readdir;
    initrd_root->finddir = &initrd_finddir;
    initrd_root->ptr = 0;
    initrd_root->impl = 0;

    initrd_dev = (fs_node_t *) kmalloc(sizeof(fs_node_t));
    initrd_dev->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->len = 0;
    initrd_dev->flags = FS_DIR;
    initrd_dev->read = 0;
    initrd_dev->write = 0;
    initrd_dev->open = 0;
    initrd_dev->close = 0;
    initrd_dev->readdir = &initrd_readdir;
    initrd_dev->finddir = &initrd_finddir;
    initrd_dev->ptr = 0;
    initrd_dev->impl = 0;

    root_nodes = (fs_node_t *) kmalloc(sizeof(fs_node_t *) * initrd_head->nfiles);
    nroot_nodes = initrd_head->nfiles;

    for (int i = 0; i < initrd_head->nfiles; i++) {
        fhead[i].off += loc;

        strcpy(root_nodes[i].name, &fhead[i].name);
        root_nodes[i].mask = root_nodes[i].uid = root_nodes[i].gid = 0;
        root_nodes[i].len = fhead[i].len;
        root_nodes[i].inode = i;
        root_nodes[i].flags = FS_FILE;
        root_nodes[i].read = &initrd_read;
        root_nodes[i].write = 0;
        root_nodes[i].open = 0;
        root_nodes[i].close = 0;
        root_nodes[i].readdir = 0;
        root_nodes[i].finddir = 0;
        root_nodes[i].impl = 0;
    }

    return initrd_root;
}