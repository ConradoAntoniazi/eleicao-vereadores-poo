import java.util.List;

public class Eleicao {
    private String cidade;
    private List<Candidato> candidatos;
    private List<Partido> partidos;
    
    public Eleicao(String cidade) {
        this.cidade = cidade;
    }
    
    public String getCidade() {
        return cidade;
    }
    public void setCidade(String cidade) {
        this.cidade = cidade;
    }

    public void processarCandidatos(String caminhoArquivo) {
        // Lógica para ler e processar o CSV de candidatos
    }

    public void processarVotos(String caminhoArquivo) {
        // Lógica para ler e processar o CSV de votação
    }

    public void gerarRelatorios() {
        // Geração dos relatórios exigidos
    }
}
