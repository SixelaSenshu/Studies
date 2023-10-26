class ObjVLispFabrique {

    private static ObjVLisp environment = new ObjVLispInstance();

    private ObjVLispFabrique() {
    }

    public static ObjVLisp nouveau() {
        return environment;
    }
}