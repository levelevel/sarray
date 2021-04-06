//文字列版動的配列（アレイ）
//
//## 機能
//- データ：文字列
//- 追加・削除・複製・push・pop・サイズ指定・サイズ固定

//アレイのデータ型
typedef char sarray_char_t;

//ポインタ版動的配列
typedef struct sarray {
    int len;
    int size_fixed; //配列サイズ固定済み
    int capacity;
    sarray_char_t *buckets;
} sarray_t;

//アレイをアロケートする。
sarray_t *new_sarray(int size);

//アレイを開放する。
void free_sarray(sarray_t *sarray);

//アレイのサイズ(sarray->len)を取得する。
int len_array(const sarray_t *sarray);

//アレイのサイズを設定する。アレイのサイズは自動的に拡張される。
void set_sarray_len(sarray_t *sarray, int size);

//アレイのidx番目にデータを格納する。アレイのサイズは自動的に拡張される。
//データ未設定の領域にはNULLが設定される。
void put_sarray(sarray_t *sarray, int idx, sarray_char_t chr);

//アレイのidx番目のデータを取得する。アレイのサイズは変わらない。
sarray_char_t get_sarray(const sarray_t *sarray, int idx);

//アレイのidx番目のデータを削除する。以降のデータは前に詰められる。アレイのサイズは1減る。
void del_sarray(sarray_t *sarray, int idx);

//アレイの最後にデータを1個追加する。アレイのサイズは1増える。
void push_sarray(sarray_t *sarray, sarray_char_t chr);

//アレイの最後のデータを1個取り出す。アレイのサイズは1減る。
sarray_char_t pop_sarray(sarray_t *sarray);

//アレイを複製する。
//複製されたアレイの内部データは必要最低限分が確保される。
sarray_t *dup_sarray(sarray_t *sarray);

//配列サイズを固定する。
//以降、配列サイズを変更するアクセス（push_sarray/pop_sarray等）はエラーとなる。
void fix_sarray_size(sarray_t *sarray);

//配列サイズ固定を解除する。
#define unfix_sarray_size(array) (array)->size_fixed=0
