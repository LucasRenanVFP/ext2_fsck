#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<linux/fs.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#define block_size (1024 << super.s_log_block_size)
#define BASE_OFFSET 1024
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*block_size) 
#define EXT2_NDIR_BLOCKS    12
#define EXT2_IND_BLOCK      EXT2_NDIR_BLOCKS
#define EXT2_DIND_BLOCK     (EXT2_IND_BLOCK + 1)
#define EXT2_TIND_BLOCK     (EXT2_DIND_BLOCK + 1)
#define EXT2_N_BLOCKS     (EXT2_TIND_BLOCK + 1)
/*typedef int __le32;
typedef short int __le16;
typedef unsigned int __u32;
typedef unsigned short int __u16;
typedef unsigned short int __u8;
*/
struct ext2_super_block {
  __le32  s_inodes_count;   /* Inodes count */
  __le32  s_blocks_count;   /* Blocks count */
  __le32  s_r_blocks_count; /* Reserved blocks count */
  __le32  s_free_blocks_count;  /* Free blocks count */
  __le32  s_free_inodes_count;  /* Free inodes count */
  __le32  s_first_data_block; /* First Data Block */
  __le32  s_log_block_size; /* Block size */
  __le32  s_log_frag_size;  /* Fragment size */
  __le32  s_blocks_per_group; /* # Blocks per group */
  __le32  s_frags_per_group;  /* # Fragments per group */
  __le32  s_inodes_per_group; /* # Inodes per group */
  __le32  s_mtime;    /* Mount time */
  __le32  s_wtime;    /* Write time */
  __le16  s_mnt_count;    /* Mount count */
  __le16  s_max_mnt_count;  /* Maximal mount count */
  __le16  s_magic;    /* Magic signature */
  __le16  s_state;    /* File system state */
  __le16  s_errors;   /* Behaviour when detecting errors */
  __le16  s_minor_rev_level;  /* minor revision level */
  __le32  s_lastcheck;    /* time of last check */
  __le32  s_checkinterval;  /* max. time between checks */
  __le32  s_creator_os;   /* OS */
  __le32  s_rev_level;    /* Revision level */
  __le16  s_def_resuid;   /* Default uid for reserved blocks */
  __le16  s_def_resgid;   /* Default gid for reserved blocks */
  /*
   * These fields are for EXT2_DYNAMIC_REV superblocks only.
   *
   * Note: the difference between the compatible feature set and
   * the incompatible feature set is that if there is a bit set
   * in the incompatible feature set that the kernel doesn't
   * know about, it should refuse to mount the filesystem.
   * 
   * e2fsck's requirements are more strict; if it doesn't know
   * about a feature in either the compatible or incompatible
   * feature set, it must abort and not try to meddle with
   * things it doesn't understand...
   */
  __le32  s_first_ino;    /* First non-reserved inode */
  __le16  s_inode_size;    /* size of inode structure */
  __le16  s_block_group_nr;   /* block group # of this superblock */
  __le32  s_feature_compat;   /* compatible feature set */
  __le32  s_feature_incompat;   /* incompatible feature set */
  __le32  s_feature_ro_compat;  /* readonly-compatible feature set */
  __u8  s_uuid[16];   /* 128-bit uuid for volume */
  char  s_volume_name[16];  /* volume name */
  char  s_last_mounted[64];   /* directory where last mounted */
  __le32  s_algorithm_usage_bitmap; /* For compression */
  /*
   * Performance hints.  Directory preallocation should only
   * happen if the EXT2_COMPAT_PREALLOC flag is on.
   */
  __u8  s_prealloc_blocks;  /* Nr of blocks to try to preallocate*/
  __u8  s_prealloc_dir_blocks;  /* Nr to preallocate for dirs */
  __u16 s_padding1;
  /*
   * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
   */
  __u8  s_journal_uuid[16]; /* uuid of journal superblock */
  __u32 s_journal_inum;   /* inode number of journal file */
  __u32 s_journal_dev;    /* device number of journal file */
  __u32 s_last_orphan;    /* start of list of inodes to delete */
  __u32 s_hash_seed[4];   /* HTREE hash seed */
  __u8  s_def_hash_version; /* Default hash version to use */
  __u8  s_reserved_char_pad;
  __u16 s_reserved_word_pad;
  __le32  s_default_mount_opts;
  __le32  s_first_meta_bg;  /* First metablock block group */
  __u32 s_reserved[190];  /* Padding to the end of the block */
};


struct ext2_inode {
  __le16  i_mode;   /* File mode */
  __le16  i_uid;    /* Low 16 bits of Owner Uid */
  __le32  i_size;   /* Size in bytes */
  __le32  i_atime;  /* Access time */
  __le32  i_ctime;  /* Creation time */
  __le32  i_mtime;  /* Modification time */
  __le32  i_dtime;  /* Deletion Time */
  __le16  i_gid;    /* Low 16 bits of Group Id */
  __le16  i_links_count;  /* Links count */
  __le32  i_blocks; /* Blocks count */
  __le32  i_flags;  /* File flags */
  union {
    struct {
      __le32  l_i_reserved1;
    } linux1;
    struct {
      __le32  h_i_translator;
    } hurd1;
    struct {
      __le32  m_i_reserved1;
    } masix1;
  } osd1;       /* OS dependent 1 */
  __le32  i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
  __le32  i_generation; /* File version (for NFS) */
  __le32  i_file_acl; /* File ACL */
  __le32  i_dir_acl;  /* Directory ACL */
  __le32  i_faddr;  /* Fragment address */
  union {
    struct {
      __u8  l_i_frag; /* Fragment number */
      __u8  l_i_fsize;  /* Fragment size */
      __u16 i_pad1;
      __le16  l_i_uid_high; /* these 2 fields    */
      __le16  l_i_gid_high; /* were reserved2[0] */
      __u32 l_i_reserved2;
    } linux2;
    struct {
      __u8  h_i_frag; /* Fragment number */
      __u8  h_i_fsize;  /* Fragment size */
      __le16  h_i_mode_high;
      __le16  h_i_uid_high;
      __le16  h_i_gid_high;
      __le32  h_i_author;
    } hurd2;
    struct {
      __u8  m_i_frag; /* Fragment number */
      __u8  m_i_fsize;  /* Fragment size */
      __u16 m_pad1;
      __u32 m_i_reserved2[2];
    } masix2;
  } osd2;       /* OS dependent 2 */
};

struct ext2_dir_entry {
  __le32  inode;         /* Inode number */
  __le16  rec_len;       /* Directory entry length */
  __le16  name_len;      /* Name length */
  char    name[];        /* File name, up to EXT2_NAME_LEN */
};

struct ext2_group_desc
{
  __le32  bg_block_bitmap;    /* Blocks bitmap block */
  __le32  bg_inode_bitmap;    /* Inodes bitmap block */
  __le32  bg_inode_table;   /* Inodes table block */
  __le16  bg_free_blocks_count; /* Free blocks count */
  __le16  bg_free_inodes_count; /* Free inodes count */
  __le16  bg_used_dirs_count; /* Directories count */
  __le16  bg_pad;
  __le32  bg_reserved[3];
};


int alpha(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int ok_super(int sd) { 
  struct ext2_super_block super;
  lseek(sd, 1024, SEEK_SET);
  read(sd, &super, sizeof(super));
  printf("magic is %d\n", super.s_magic);
  if(super.s_magic != 0xEF53) {//super block esta errado
    return 0;
  }
  return 1;
  
}

void fix_super(int sd) {
  printf("sd = %d\n", sd);
  struct ext2_super_block super;
  fprintf(stderr, "Tentando backup em 8193\n");
  lseek(sd, 1024 * 8193, SEEK_SET);
  printf("BLOCK SIZE %d\n", block_size);
  read(sd, &super, sizeof(super));
  printf("magic 8 = %d\n", super.s_magic);
  lseek(sd, 1024, SEEK_SET);
  write(sd, &super, sizeof(super));
  if(ok_super(sd)) return;
  
  fprintf(stderr, "Tentando backup em 16384\n");
  lseek(sd, 2048 * 16383 + 1024, SEEK_SET);
  read(sd, &super, sizeof(super));
  printf("magic 16 = %d\n", super.s_magic);
  lseek(sd, 1024, SEEK_SET);
  write(sd, &super, sizeof(super));
  if(ok_super(sd)) return;
  
  fprintf(stderr, "Tentando backup em 32768\n");
  lseek(sd, 32767 * 4096 + 1024, SEEK_SET);
  read(sd, &super, sizeof(super));
  printf("magic 32 = %d\n", super.s_magic);
  lseek(sd, 1024, SEEK_SET);
  write(sd, &super, sizeof(super));
}


int get_answer() {
  char answer = ' ';
  while(!alpha(answer)) answer = getchar();
  if(answer == 'Y' || answer == 'y') {
    printf("\n");
    return 1;
  }
  printf("\n");
  return 0;
}

void treat_super(int sd) {
  fprintf(stderr, "Testando super bloco\n");
  if(!ok_super(sd)) {
    printf("Erro no superbloco. Deseja consertar? (Y/N)");
    if(get_answer()) fix_super(sd);
  }
}

void remove_inode(int group, int sd, int index) {
  struct ext2_group_desc desc;
  struct ext2_super_block super;
  lseek(sd, 1024, SEEK_SET);
  read(sd, &super, sizeof(super));
  lseek(sd, BASE_OFFSET + block_size + group * sizeof(desc), SEEK_SET);
  read(sd, &desc, sizeof(desc));

  int i_bitmap_position = desc.bg_inode_bitmap;
  int inode_bitmap[block_size >> 4];
  lseek(sd, BLOCK_OFFSET(i_bitmap_position), SEEK_SET);
  read(sd, &inode_bitmap, sizeof(inode_bitmap));
  int id1 = index / 32;//Cada inteiro do bitmap tem 32 inodes correspondentes. Index 0-based
  int id2 = index % 32;
  for(int i = 0; i < 10; i++) printf("%d bitmap = %d\n", i, inode_bitmap[i]);
  
  if(inode_bitmap[id1] & (1ll << id2)) {//Se o indice consta no inode_bitmap
    inode_bitmap[id1] ^= (1ll << id2);
  }
  else fprintf(stderr, "Tentando remover um inode ja removido\n");
  lseek(sd, BLOCK_OFFSET(i_bitmap_position), SEEK_SET);
  write(sd, &inode_bitmap, sizeof(inode_bitmap));
}

void treat_multi_own(int group, int sd, int *taken) {
  struct ext2_super_block super;
  fprintf(stderr, "Procurando dono multiplo de bloco\n");
  lseek(sd, 1024, SEEK_SET);
  read(sd, &super, sizeof(super));

  struct ext2_group_desc desc;
  struct ext2_inode inode;
  lseek(sd, BASE_OFFSET + block_size + group * sizeof(desc), SEEK_SET);//group descriptor do grupo group
  read(sd, &desc, sizeof(desc));
  for(int i = 0; i < super.s_inodes_per_group; i++) {
    int inode_position = BLOCK_OFFSET(desc.bg_inode_table) + i * sizeof(inode);
    lseek(sd, inode_position, SEEK_SET);
    read(sd, &inode, sizeof(inode));
    if(inode.i_size == 0) continue;
    
    int finished = 0;
    for(int j = 0; j < 12; j++) {//direct-block
      int block = inode.i_block[j];
      if(block == 0) {
        finished = 1;
        break;
      }
      if(taken[block]) {
        printf("Bloco %d com mais de um dono. Deseja remover um dos inodes? (Y/N)", block);
        if(get_answer()) remove_inode(group, sd, i);
      }
      taken[block] = 1;
    }
    if(finished) continue;

    int indirect_position = inode.i_block[12];
    if(indirect_position == 0) continue;
    int indirect_blocks[block_size >> 2];
    lseek(sd, BLOCK_OFFSET(indirect_position), SEEK_SET);
    read(sd, &indirect_blocks, sizeof(indirect_blocks));
    for(int j = 0; j < block_size >> 2; j++) {
      int block = indirect_blocks[j];
      if(block == 0) {
        finished = 1;
        break;
      }
      if(taken[block]) {
        printf("Bloco %d com mais de um dono. Deseja remover um dos inodes? (Y/N)", block);
        if(get_answer()) remove_inode(group, sd, i);
      }
      taken[block] = 1;
    }
    if(finished) continue;

    int doubly_position = inode.i_block[13];
    if(doubly_position == 0) continue;
    int doubly_blocks[block_size >> 2];
    lseek(sd, BLOCK_OFFSET(doubly_position), SEEK_SET);
    read(sd, &doubly_blocks, sizeof(doubly_blocks));
    for(int k = 0; k < block_size >> 2; k++) {
      if(finished) break;
      if(doubly_blocks[k] == 0) {
        finished = 1;
        break;
      }
      lseek(sd, BLOCK_OFFSET(doubly_blocks[k]), SEEK_SET);
      read(sd, &indirect_blocks, sizeof(indirect_blocks));
      for(int j = 0; j < block_size >> 2; j++) {
        int block = indirect_blocks[j];
        if(block == 0) {
          finished = 1;
          break;
        }
        if(taken[block]) {
          printf("Bloco %d com mais de um dono. Deseja remover um dos inodes? (Y/N)", block);
          if(get_answer()) remove_inode(group, sd, i);
        }
        taken[block] = 1;
      }
    }
    if(finished) continue;

    int triply_position = inode.i_block[14];
    if(triply_position == 0) continue;
    int triply_blocks[block_size >> 2];
    lseek(sd, BLOCK_OFFSET(triply_position), SEEK_SET);
    read(sd, &triply_blocks, sizeof(triply_blocks));
    for(int x = 0; x < block_size >> 2; x++) {
      if(finished) break;
      if(triply_blocks[x] == 0) {
        break;
      }
      lseek(sd, BLOCK_OFFSET(triply_blocks[x]), SEEK_SET);
      read(sd, &doubly_blocks, sizeof(doubly_blocks));
      for(int k = 0; k < block_size >> 2; k++) {
        if(finished) break;
        if(doubly_blocks[k] == 0) {
          finished = 1;
          break;
        }
        lseek(sd, BLOCK_OFFSET(doubly_blocks[k]), SEEK_SET);
        read(sd, &indirect_blocks, sizeof(indirect_blocks));
        for(int j = 0; j < block_size >> 2; j++) {
          int block = indirect_blocks[j];
          if(block == 0) {
            finished = 1;
            break;
          }
          if(taken[block]) {
            printf("Bloco %d com mais de um dono. Deseja remover um dos inodes? (Y/N)", block);
            if(get_answer()) remove_inode(group, sd, i);
          }
          taken[block] = 1;
        }
      }
    }
  }
}

void treat_permission(int group, int sd) {
  struct ext2_super_block super;
  fprintf(stderr, "Procurando inode com permissao zerada\n");
  lseek(sd, 1024, SEEK_SET);
  read(sd, &super, sizeof(super));
  
  struct ext2_group_desc desc;
  struct ext2_inode inode;
  lseek(sd, BASE_OFFSET + group * sizeof(desc), SEEK_SET);
  read(sd, &desc, sizeof(desc));
  struct ext2_group_desc desc2;
  lseek(sd, BASE_OFFSET + block_size, SEEK_SET);
  read(sd, &desc2, sizeof(desc2));
  
  for(int i = 0; i < super.s_inodes_per_group; i++) {
    int inode_position = BLOCK_OFFSET(desc.bg_inode_table) + i * sizeof(inode);
    lseek(sd, inode_position, SEEK_SET);
    read(sd, &inode, sizeof(inode));
    if(inode.i_size == 0) continue;
    if(inode.i_mode == 0) {
      printf("Inode %d tem permissoes zeradas. Deseja alterar as permissoes? (Y/N)", i + super.s_inodes_per_group * group);
      if(get_answer()) {
        printf("Digite um inteiro correspondente a permissao desejada.\n");
        int perm;
        scanf("%d", &perm);
        inode.i_mode = perm;
        lseek(sd, inode_position, SEEK_SET);
        write(sd, &inode, sizeof(inode));
      }
    }
  }
}

char *int_to_string(int number) {
  char *ret = malloc(sizeof(char) * 20);
  if(number == 0) {
    ret[0] = '0';
    ret[1] = '\0';
    return ret;
  }
  int len = 0;
  int n = number;
  while(n > 0) {
    len++, n /= 10;
  }
  n = number;
  ret[len--] = '\0';
  while(n > 0) {
    ret[len--] = '0' + n % 10;
    n /= 10;
  }
  return ret;
}

void lost_found(int sd, int inode_position, int inode_index, char *argv1) {
  char filename[50];
  strcpy(filename, argv1);
  int sz = strlen(filename);
  while(sz > 0 && filename[sz - 1] != '/') {
    filename[sz - 1] = '\0';
    sz--;
  }
  if(sz == 0) strcat(filename, "./");
  strcat(filename, "lost+found/");
  mkdir(filename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  strcat(filename, "#");
  char *inode_number = int_to_string(inode_index);
  strcat(filename, inode_number);
  int fd = open(filename, O_RDWR | O_CREAT, 0666);
  struct ext2_inode inode;
  lseek(sd, inode_position, SEEK_SET);
  read(sd, &inode, sizeof(inode));
  lseek(fd, 0, SEEK_SET);
  write(fd, &inode, sizeof(inode));
}

void treat_orphans(int group, int sd, char *argv1) {
  struct ext2_super_block super;
  fprintf(stderr, "Procurando inodes orfaos\n");
  lseek(sd, 1024, SEEK_SET);
  read(sd, &super, sizeof(super));
  
  struct ext2_group_desc desc;
  struct ext2_inode inode;
  lseek(sd, BASE_OFFSET + block_size + group * sizeof(desc), SEEK_SET);
  read(sd, &desc, sizeof(desc));
  
  for(int i = 0; i < super.s_inodes_per_group; i++) {
    int inode_position = BLOCK_OFFSET(desc.bg_inode_table) + i * sizeof(inode);
    lseek(sd, inode_position, SEEK_SET);
    read(sd, &inode, sizeof(inode));
    if(inode.i_size == 0) continue;
    if(inode.i_links_count == 0) {
      printf("Inode %d nao tem diretorio. Deseja adiciona-lo a lost+found? (Y/N)", i + super.s_inodes_per_group * group);
      if(get_answer()) {
        lost_found(sd, inode_position, super.s_inodes_per_group * group + i, argv1);        
      }
    }
  }
}

int main(int argc, char **argv) {
  int sd = open(argv[1], O_RDWR);
  treat_super(sd);
  if(!ok_super(sd)) return 0;
  fprintf(stderr, "Super bloco ok\n\n\n");
   
  struct ext2_group_desc desc;
  struct ext2_super_block super;
  lseek(sd, BASE_OFFSET, SEEK_SET);
  read(sd, &super, sizeof(super));
  lseek(sd, BASE_OFFSET + block_size, SEEK_SET);
  read(sd, &desc, sizeof(desc));
  unsigned int group_count = 1 + (super.s_blocks_count-1) / super.s_blocks_per_group;
  int *taken;//1 se o bloco ja tem dono. 0 caso contrario
  taken = malloc(((super.s_blocks_per_group * group_count) * 4 + 5) * sizeof(int));
  memset(taken, 0, sizeof(taken));
  for(int i = 0; i < group_count; i++) {
    fprintf(stderr, "Resolvendo para o grupo de blocos %d\n", i);

    treat_multi_own(i, sd, taken);
    fprintf(stderr, "Bloco com dois inodes resolvido\n\n\n");
  
    treat_permission(i, sd);
    fprintf(stderr, "Permissao resolvida\n\n\n");
  
    treat_orphans(i, sd, argv[1]);
    fprintf(stderr, "Orfaos resolvidos\n\n\n");
  }
  return 0;
}
