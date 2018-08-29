
/*
 * this code shows how to use container_off
 * to get the container of a pointer
 * and also to get the container of the container
 * to vmr() - get the verbs_mr wrapping ibv_mr
 * to_mmr() - gets the mlx5_mr wrapping the verbs_mr the wraps the ibv_mr
 *
 */

#include <stdlib.h>
#include <stddef.h>


#define check_types_match(expr1, expr2)		\
	((typeof(expr1) *)0 != (typeof(expr2) *)0)

#define container_off(containing_type, member)	\
	offsetof(containing_type, member)

#define container_of(member_ptr, containing_type, member)		\
	 ((containing_type *)						\
	  ((char *)(member_ptr)						\
	   - container_off(containing_type, member))			\
	  + check_types_match(*(member_ptr), ((containing_type *)0)->member))

struct ibv_mr {
	int x;
	int y;
};

enum ibv_mr_type {
	IBV_MR_TYPE_MR,
	IBV_MR_TYPE_NULL_MR,
};

struct verbs_mr {
	struct ibv_mr		ibv_mr;
	enum ibv_mr_type        mr_type;
};

struct mlx5_mr {
	struct verbs_mr vmr;
	char            *buf;
};


static inline struct verbs_mr *to_vmr(struct ibv_mr *ibmr)
{
	return container_of(ibmr, struct verbs_mr, ibv_mr);
}

static inline struct mlx5_mr *to_mmr(struct ibv_mr *ibmr)
{
	return container_of(ibmr, struct mlx5_mr, vmr.ibv_mr);
}


int main()
{
	struct mlx5_mr *mlx5mr;
	struct mlx5_mr *mmr =NULL;
	struct ibv_mr *ibvmr;
	struct verbs_mr *vmr;

	mlx5mr = malloc(sizeof(*mlx5mr));

	ibvmr = &mlx5mr->vmr.ibv_mr;


	mlx5mr->vmr.ibv_mr.x = 1;
	mlx5mr->vmr.ibv_mr.y = 11;
	mlx5mr->vmr.mr_type = IBV_MR_TYPE_NULL_MR;

	mmr = to_mmr(ibvmr);
	vmr = to_vmr(ibvmr);

	free(mlx5mr);



	return 0;
}


