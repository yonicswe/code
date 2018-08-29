
why use not not !! when you can just not use the !! at all ?
what is the difference between
	qp->scat_cqe = (ucmd.flags & MLX5_QP_FLAG_SCATTER_CQE);
and
	qp->scat_cqe = !!(ucmd.flags & MLX5_QP_FLAG_SCATTER_CQE);

answer
ucmd.flags & MLX5_QP_FLAG_SCATTER_CQE
when MLX5_QP_FLAG_SCATTER_CQE = 1<<1;
will result in 2 (when flags is set with bit 1)
whereas 
	!!(ucmd.flags & MLX5_QP_FLAG_SCATTER_CQE)
will result with 1 (when flags is set with bit 1)

	its called logical yes operator

https://stackoverflow.com/questions/10307281/c-operator-is-a-two-not
