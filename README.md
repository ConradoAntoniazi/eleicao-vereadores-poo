# 📰 Apurador de Eleicao para Vereadores

---

Este projeto em **Java** processa os resultados da eleição municipal para **vereadores**, utilizando dados oficiais do TSE (Tribunal Superior Eleitoral). Com ele, você pode analisar facilmente os votos nominais, votos de legenda, eleitos, suplentes e muito mais!

---

## ✨ O que este programa faz?

A partir de dois arquivos CSV disponibilizados pelo TSE e do código de um município, o programa:

- Lê os dados de **candidatos**;
- Analisa os dados de **votação por seção**;
- Filtra e processa apenas os dados do município informado;
- Exibe um **relatório completo no terminal** com os resultados da eleição municipal!

---

## 📆 Onde conseguir os dados?

Os dados estão disponíveis gratuitamente no site do TSE:

- **Candidatos**:  
  https://cdn.tse.jus.br/estatistica/sead/odsele/consulta_cand/consulta_cand_2024.zip

- **Votação por seção** (troque `AC` pela sigla do estado desejado):  
  https://cdn.tse.jus.br/estatistica/sead/odsele/votacao_secao/votacao_secao_2024_AC.zip

Depois de extrair os `.csv`, você está pronto para começar.

---

## 🚀 Como compilar e executar

Este projeto segue a estrutura padrão de "Java Project", com os códigos-fonte em `src/` e arquivos `.class` sendo gerados em `bin/`.

### Opção 1: Usando o `build.xml` (caso tenha Apache Ant instalado)

Compile com:
```bash
ant compile
```

Execute com:
```bash
ant run -DcdMunicipio=<seu_codigo_aqui>
```

Gere o `.jar` com:
```bash
ant jar
```

Limpe o projeto com:
```bash
ant clean
```

### Opção 2: Manualmente (sem Ant)

Compile os arquivos:
```bash
javac -d bin src/**/*.java
```

Execute o programa:
```bash
java -cp bin App <codigo_municipio> <arquivo_csv_candidatos> <arquivo_csv_votacao> <data_eleicao>
```

#### Exemplo:
```bash
java -cp bin App 57053 candidatos.csv votacao.csv 06/10/2024
```

---

## 📁 Estrutura de diretórios

```
├── bin/                        # Arquivos .class gerados
├── src/                        # Código-fonte Java
├── build.xml                   # Script de build para Apache Ant
├── trabalho1-poo-2024-2.pdf    # Documento com a especificação do trabalho
└── README.md                   # Este arquivo
```

---

## 🎓 Créditos

Projeto acadêmico para a disciplina de **Programação Orientada a Objetos**, sob orientação do Prof. **João Paulo A. Almeida**.

---

- Uma versão em c++ desse projeto pode ser encontrada aqui:
  https://github.com/raphaelitos/Eleicao-Vereadores-cpp.git

---

Boa análise eleitoral! 🌟
