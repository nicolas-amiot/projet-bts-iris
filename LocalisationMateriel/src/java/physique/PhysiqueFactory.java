package physique;

public class PhysiqueFactory {

    private static BatimentDataService batimentDataSrv = null;
    private static LecteurRFIDDataService lecteurRFIDDataSrv = null;
    private static LocalisationDataService localisationDataSrv = null;
    private static MaterielDataService materielDataSrv = null;
    private static MetrologueDataService metrologueDataSrv = null;
    private static PortiqueDataService portiqueDataSrv = null;
    private static SalleDataService salleDataSrv = null;
    private static TypeDataService typeDataSrv = null;

    public static BatimentDataService getBatimentDataService() {
        if(batimentDataSrv == null){
            batimentDataSrv = new BatimentDataServiceImpl();
        }
        return batimentDataSrv;
    }
    
    public static LecteurRFIDDataService getLecteurRFIDDataService(){
        if(lecteurRFIDDataSrv == null){
            lecteurRFIDDataSrv = new LecteurRFIDDataServiceImpl();
        }
        return lecteurRFIDDataSrv;
    }
    
    public static LocalisationDataService getLocalisationDataService(){
        if(localisationDataSrv == null){
            localisationDataSrv = new LocalisationDataServiceImpl();
        }
        return localisationDataSrv;
    }
    
    public static MaterielDataService getMaterielDataService() {
        if (materielDataSrv == null) {
            materielDataSrv = new MaterielDataServiceImpl();
        }
        return materielDataSrv;
    }
    
    public static MetrologueDataService getMetrologueDataService(){
        if(metrologueDataSrv == null){
            metrologueDataSrv = new MetrologueDataServiceImpl();
        }
        return metrologueDataSrv;
    }
    
    public static PortiqueDataService getPortiqueDataService(){
        if(portiqueDataSrv == null){
            portiqueDataSrv = new PortiqueDataServiceImpl();
        }
        return portiqueDataSrv;
    }
    
    public static SalleDataService getSalleDataService(){
        if(salleDataSrv == null){
            salleDataSrv = new SalleDataServiceImpl();
        }
        return salleDataSrv;
    }

    public static TypeDataService getTypeDataService() {
        if (typeDataSrv == null) {
            typeDataSrv = new TypeDataServiceImpl();
        }
        return typeDataSrv;
    }
}
