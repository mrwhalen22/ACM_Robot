        void  DisableInterrupts(void);
        void  EnableInterrupts(void);
        uint32_t  StartCritical(void);
        void  EndCritical(uint32_t saved_PRIMASK);
        void  WaitForInterrupt(void);

