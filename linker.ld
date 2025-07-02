ENTRY(start)  /* Point d'entrée défini dans boot.s */

SECTIONS
{
  /* L'adresse de chargement en mémoire */
  . = 0x100000;  /* 1 Mio, conventionnel pour les kernels */

  /* Section code */
  .text : {
    *(.text)
  }

  /* Section données initialisées */
  .data : {
    *(.data)
  }

  /* Section données non initialisées (BSS) */
  .bss : {
    *(.bss COMMON)
  }
}
