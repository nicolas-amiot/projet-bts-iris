package metier;


public class MetierFactory {
    
    private static BatimentService batimentSrv = null;
    private static LecteurRFIDService lecteurRFIDSrv = null;
    private static LocalisationService localisationSrv = null;
    private static MaterielService materielSrv = null;
    private static MetrologueService metrologueSrv = null;
    private static PortiqueService portiqueSrv = null;
    private static SalleService salleSrv = null;
    private static TypeService typeSrv = null;

    public static BatimentService getBatimentService() {
        if(batimentSrv == null){
            batimentSrv = new BatimentServiceImpl();
        }
        return batimentSrv;
    }
    
    public static LecteurRFIDService getLecteurRFIDService(){
        if(lecteurRFIDSrv == null){
            lecteurRFIDSrv = new LecteurRFIDServiceImpl();
        }
        return lecteurRFIDSrv;
    }
    
    public static LocalisationService getLocalisationService(){
        if(localisationSrv == null){
            localisationSrv = new LocalisationServiceImpl();
        }
        return localisationSrv;
    }
    
    public static MaterielService getMaterielService() {
        if (materielSrv == null) {
            materielSrv = new MaterielServiceImpl();
        }
        return materielSrv;
    }
    
    public static MetrologueService getMetrologueService(){
        if(metrologueSrv == null){
            metrologueSrv = new MetrologueServiceImpl();
        }
        return metrologueSrv;
    }
    
    public static PortiqueService getPortiqueService(){
        if(portiqueSrv == null){
            portiqueSrv = new PortiqueServiceImpl();
        }
        return portiqueSrv;
    }
    
    public static SalleService getSalleService(){
        if(salleSrv == null){
            salleSrv = new SalleServiceImpl();
        }
        return salleSrv;
    }
    
    public static TypeService getTypeService() {
        if (typeSrv == null) {
            typeSrv = new TypeServiceImpl();
        }
        return typeSrv;
    }
}
