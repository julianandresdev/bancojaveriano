# 💰 Banco Javeriano - C++

Bienvenido al sistema bancario **Banco Javeriano**, una aplicación desarrollada en **C++** que simula la gestión de un banco real con funcionalidades completas para clientes, cuentas, operaciones y estadísticas financieras.

Este proyecto se enfoca en el uso de **POO (Programación Orientada a Objetos)**, manejo de punteros, herencia, composición y persistencia de datos con archivos `.json`.

---

## 🏛️ Clases principales del proyecto

### 🧍 Clientes
- Cada cliente tiene: `id`, `nombre`, `dirección`.
- Contiene un vector de cuentas (`Ahorros` o `Corriente`).
- Métodos clave:
  - `agregarCuenta()`
  - `mostrarCuentas()`
  - `aplicarIntereses()`
  - `consignar()` / `retirar()`
  - `contarCuentas()`
  - `promedioSaldo()`
  - Sobrecarga del `<<` para imprimir clientes fácilmente

> 💡 Los clientes se guardan por **composición** en el Banco (no se usan punteros a clientes).

---

### 🏦 Cuentas (Clase abstracta)
- Base para `Ahorros` y `Corriente`.
- Contiene: `id`, `saldo`.
- Métodos virtuales como `getTipo()`, `aplicarInteres()`, `toJSON()`.

### 💸 Ahorros
- Hereda de `Cuentas`.
- Añade: `tasa de interés`.
- Aplica interés al saldo.

### 🏧 Corriente
- Hereda de `Cuentas`.
- Añade: `límite de sobregiro`.
- Permite saldo negativo hasta el límite.

> Las cuentas inician en el ID **100**, y los clientes desde el ID **1**.

---

## 🖥️ Interfaz por consola

```text
===== MENU BANCO JAVERIANO =====
1) MANTENIMIENTO DE CLIENTES
   1.1) Agregar Cliente
   1.2) Listar Clientes
2) MANTENIMIENTO DE CUENTAS
   2.1) Agregar Cuenta
   2.2) Listar Cuentas
3) ESTADÍSTICAS
   3.1) Total de Clientes
   3.2) Total de Cuentas
   3.3) Promedio del Saldo de las Cuentas
   3.4) Número de Cuentas de Ahorro
   3.5) Número de Cuentas Corrientes
4) OPERACIONES FINANCIERAS
   4.1) Aplicar Tasa de Interés a Cuentas de Ahorro
   4.2) Consignar Dinero en una Cuenta
   4.3) Retirar Dinero de una Cuenta
5) SALIR
   5.1) Guardar los datos en BancoJaveriano.json y cerrar el programa
================================
