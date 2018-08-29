/*typedef*/ union iser_pdu_bhs_t{

    unsigned char       buf[48];

    struct {
        unsigned char         opcode;     /* optional bits + opcode */
        unsigned char         flags;      /* opcode-specific flags */
        unsigned char         rsvd2[2];   /* usually reserved, used in response */
        unsigned char         ahs_length; /* AHS total length */
        unsigned char         dlength[3]; /* Data segment length */
        unsigned char         lun[8];     /* LUN */
        unsigned char         itt[4];	    /* Initiator Task Tag */
        unsigned char         other[28];  /* opcode-specific */
    } byte;

}yoni;//iser_pdu_bhs_t;


int
main(void)
{

	//union iser_pdu_bhs_t yoni;
	memset(&yoni.buf, 1 , sizeof(yoni.buf) );


	return 0;
}

